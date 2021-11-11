//
// Created by ivan on 08.11.2021.
//

// #include "lib.h"

void swap(int *first, int *second) {
    int buf = *first;
    *first = *second;
    *second = buf;
}

int *my_sort(int *array, int arr_size) {
    for (int i = 0; i < arr_size - 1; ++i) {
        for (int j = i + 1; j < arr_size; ++j) {
            if (array[j] < array[i]) swap(&array[j], &array[i]);
        }
    }
    return array;
}

int test(int *array, int arr_size) {
    int res = 0;
    for (int i = 1; i < arr_size; ++i) {
        if (array[i] < array[i - 1])
            ++res;
    }
    return res;
}
