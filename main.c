#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lib.h"

int main() {
    srand(time(NULL));
    printf("Введите число элементов: ");
    int size;
    scanf("%d", &size);
    int array[size];
    for (int i = 0; i < size; ++i)
        array[i] = rand() % size;
    int *sorted_array = my_sort(array, size);
    for (int i = 0; i < size; ++i) {
        printf("%d)\t%d\n", i + 1, sorted_array[i]);
    }
    printf("Errors: %d", test(sorted_array, size));
    return 0;
}
