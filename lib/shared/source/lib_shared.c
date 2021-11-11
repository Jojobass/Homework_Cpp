//
// Created by ivan on 08.11.2021.
//
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int test(int *array, int arr_size);

void swap(int *first, int *second) {
    int buf = *first;
    *first = *second;
    *second = buf;
}

//  сортировка выбором
void small_sort(int *array, int arr_size) {
    for (int i = 0; i < arr_size - 1; ++i) {
        for (int j = i + 1; j < arr_size; ++j) {
            if (array[j] < array[i]) swap(&array[j], &array[i]);
        }
    }
}

void merge(int *arr_first, int *arr_second, int arr_size1, int arr_size2) {
    int sorted[arr_size1 + arr_size2];
    int i1 = 0, i2 = 0;
    for (int i = 0; i < arr_size1 + arr_size2; ++i) {
        if (i1 < arr_size1 && i2 < arr_size2) {
            if (arr_first[i1] <= arr_second[i2]) {
                sorted[i] = arr_first[i1];
                ++i1;
            } else {
                sorted[i] = arr_second[i2];
                ++i2;
            }
        } else {
            if (i1 < arr_size1) {
                sorted[i] = arr_first[i1];
                ++i1;
            }
            if (i2 < arr_size2) {
                sorted[i] = arr_second[i2];
                ++i2;
            }
        }
    }
    for (int i = 0; i < arr_size1 + arr_size2; ++i) {
        arr_first[i] = sorted[i];
    }
}

int *my_sort(int *array, int arr_size) {
//    максимальное количество одновременных процессов
    int num_of_processes = sysconf(_SC_NPROCESSORS_ONLN);
//    массив с PID всех процессов
    pid_t pids[num_of_processes];
//    массив, который могут читать и изменять все процессы
    int *shared_array = mmap(NULL, arr_size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_array == MAP_FAILED)
        return 0;
    for (int i = 0; i < arr_size; ++i)
        shared_array[i] = array[i];
//    создание процессов и одновременная сортировка ~равных частей массива
    for (int i = 0; i < num_of_processes; ++i) {
        pids[i] = fork();
        if (pids[i] == 0) {
            if (i != num_of_processes - 1)
                small_sort(shared_array + (arr_size / num_of_processes) * i, arr_size / num_of_processes);
            else
                small_sort(shared_array + (arr_size / num_of_processes) * i,
                           arr_size / num_of_processes + arr_size % num_of_processes);

            exit(EXIT_SUCCESS);
        }
    }
//    проверка на зомби
    for (int i = 0; i < num_of_processes; ++i) {
        if (waitpid(pids[i], NULL, 0) != pids[i]) {
            return 0;
        }
    }
//    количество PID, которое нужно для слияния подмассивов
    int pids1_size = 0;
    for (int i = num_of_processes; i > 0; i /= 2) {
        for (int j = 2; j <= i; j += 2) {
            ++pids1_size;
        }
    }
//    массив с PID процессов для слияния подмассивов
    pid_t pids1[pids1_size];
    int pids1_cnt = 0;
//    поздание процессов и слияние подмассивов пока не останется 1 отсортированный массив
    for (int i = num_of_processes; i > 0; i /= 2) {
        for (int j = 2; j <= i; j += 2) {
            pids1[pids1_cnt] = fork();
            if (pids1[pids1_cnt] == 0) {
                int subarr_size = (arr_size - arr_size % num_of_processes) / i;
                if (j != i)
                    merge(shared_array + subarr_size * (j - 2), shared_array + subarr_size * (j - 1), subarr_size,
                          subarr_size);
                else
                    merge(shared_array + subarr_size * (j - 2), shared_array + subarr_size * (j - 1), subarr_size,
                          subarr_size + arr_size % num_of_processes);

                exit(EXIT_SUCCESS);
            }
            ++pids1_cnt;
        }
        for (int j = num_of_processes - i; j < pids1_cnt; ++j) {
            if (waitpid(pids1[j], NULL, 0) != pids1[j]) {
                return 0;
            }
        }
    }

    return shared_array;
}

int test(int *array, int arr_size) {
    int res = 0;
    for (int i = 1; i < arr_size; ++i) {
        if (array[i] < array[i - 1])
            ++res;
    }
    return res;
}
