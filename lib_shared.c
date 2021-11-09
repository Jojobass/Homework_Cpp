//
// Created by ivan on 08.11.2021.
//
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

void swap(int *first, int *second) {
    int buf = *first;
    *first = *second;
    *second = buf;
}

int SmallSort(int *array, int arr_size) {
    for (int i = 0; i < arr_size - 1; ++i) {
        for (int j = i + 1; j < arr_size; ++j) {
            if (array[j] < array[i]) swap(&array[j], &array[i]);
        }
    }
}

int Merge(int *arr_first, int *arr_second, int arr_size) {
    int sorted[arr_size * 2];
    int i1 = 0, i2 = 0;
    for (int i = 0; i < arr_size * 2; ++i) {
        if (i1 < arr_size && i2 < arr_size) {
            if (arr_first[i1] <= arr_second[i2]) {
                sorted[i] = arr_first[i1];
                ++i1;
            } else {
                sorted[i] = arr_second[i2];
                ++i2;
            }
        } else {
            if (i1 < arr_size) {
                sorted[i] = arr_first[i1];
                ++i1;
            }
            if (i2 < arr_size) {
                sorted[i] = arr_second[i2];
                ++i2;
            }
        }
    }
    for (int i = 0; i < arr_size * 2; ++i) {
        arr_first[i] = sorted[i];
    }
}

int MySort(int *array, int arr_size) {
    long num_of_processes = sysconf(_SC_NPROCESSORS_ONLN);
//    printf("%li\n", num_of_processes);
    pid_t pids[num_of_processes];
    int *shared_memory = mmap(NULL, arr_size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    if (shared_memory == MAP_FAILED) {
        return 0;
    }
    for (int i = 0; i < arr_size; ++i) {
        shared_memory[i] = array[i];
//        printf("%d\t%d\t%d\n", i, *(shared_memory + i), array[i]);
    }

    for (int i = 0; i < num_of_processes; ++i) {
        pids[i] = fork();
        if (pids[i] == 0) {
            SmallSort(shared_memory + (arr_size / num_of_processes) * i, arr_size / num_of_processes);

            exit(EXIT_SUCCESS);
        }
    }
    int status;
    for (int i = 0; i < num_of_processes; ++i) {
        if (waitpid(pids[i], &status, 0) != pids[i]) {
            return 0;
        }
        WIFEXITED(status) != 0 ? printf("1 ") : printf("0 ");
//        pids[i]=0;
    }

    for(int i=0; i<num_of_processes; i++)
        printf("%d ", pids[i]);

    for (int i = num_of_processes; i > 0; i /= 2) {
        for (int j = 0; j < i; j += 2) {
            pids[j] = fork();
            if (pids[j] == 0) {
                Merge(shared_memory + (arr_size / i) * j, shared_memory + (arr_size / i) * (j + 1), arr_size / i);

                exit(EXIT_SUCCESS);
            }
        }
        for (int j = 0; j < i/2; ++j) {
            if (waitpid(pids[j], NULL, 0) != pids[j]) {
                return 0;
            }
            pids[j]=0;
        }
    }

    for (int i = 0; i < arr_size; ++i) {
        printf("%d\t%d\t%d\n", i, shared_memory[i], array[i]);
    }
}

int main() {
    srand(time(NULL));
    int array[100000];
    for (int i = 0; i < 100000; ++i)
        array[i] = rand() % 100000;
    MySort(array, sizeof(array) / sizeof(int));

}
