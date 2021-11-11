//
// Created by ivan on 09.11.2021.
//

#include <ctime>
#include <cstdlib>

extern "C" {
#include <malloc.h>
#include "test_static.h"
#include "test_shared.h"
}

#define size 100000

int main() {
    int array[size];

    double time_static = 0;
    double time_shared = 0;

    for (int i = 0; i < 10; ++i) {
        srand(time(NULL));
        for (int j = 0; j < size; ++j)
            array[j] = rand() % size;

        clock_t begin_static = clock();
        sort(array, size);
        clock_t end_static = clock();

        time_static += (double) (end_static - begin_static) / CLOCKS_PER_SEC;

        clock_t begin_shared = clock();
        sort(array, size);
        clock_t end_shared = clock();

        time_shared += (double) (end_shared - begin_shared) / CLOCKS_PER_SEC;
    }
    printf("Время выполнения статичной библиотекой: %f\n", time_static / 10);
    printf("Время выполнения динамической библиотекой: %f\n", time_shared / 10);


    return 0;
}