#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skyscrapers.h"

int main() {
    // динамический массив
    Skyscraper *array_dynamic = (Skyscraper *) malloc(6 * sizeof(Skyscraper));
    Skyscraper array[6];
    fill(array);
    // первые 6 небоскребов заданы
    if (array_dynamic != NULL)
        memcpy(array_dynamic, array, sizeof(array));
    // размер массива
    int size_dynamic = 6;
    // ввод небоскребов с консоли
    while (1) {
        // буферный элемент
        Skyscraper elem;
        // продолжение либо выход из цикла
        printf("Create one more skyscraper (y/n)? ");
        char yn = getchar();
        if (yn != 'y') break;
        // увеличение размера массива на 1
        size_dynamic++;
        // ввод характеристик нового
        elem = add_skyscraper(size_dynamic);
        // реаллокация памяти для массива
        // array_dynamic = (Skyscraper *) realloc(array_dynamic, size_dynamic * sizeof(Skyscraper));
        Skyscraper *tmp = (Skyscraper *) realloc(array_dynamic, size_dynamic * sizeof(Skyscraper));
        if (tmp != NULL) array_dynamic = tmp;
        else {
            free(tmp);
            free(array_dynamic);
            printf("Reallocation error!");
            return 1;
        }
        // присвоение последнему элементу введенного
        array_dynamic[size_dynamic - 1] = elem;
        getchar();
    }
    // вывод массивов
    printf("Несортированный массив:\n");
    for (int i = 0; i < size_dynamic; ++i)
        printf("%d floors, %.2lf m, %.2lf m - spire, %s, %s\n",
               array_dynamic[i].num_of_floors, array_dynamic[i].height_general, array_dynamic[i].height_spire,
               array_dynamic[i].design, array_dynamic[i].region);
    printf("\n");

    printf("Массив, отсортированный по назначению:\n");
    sort_skyscrapers(array_dynamic, size_dynamic, 1);
    for (int i = 0; i < size_dynamic; ++i)
        printf("%d floors, %.2lf m, %.2lf m - spire, %s, %s\n",
               array_dynamic[i].num_of_floors, array_dynamic[i].height_general, array_dynamic[i].height_spire,
               array_dynamic[i].design, array_dynamic[i].region);
    printf("\n");

    printf("Массив, отсортированный по региону:\n");
    sort_skyscrapers(array_dynamic, size_dynamic, 2);
    for (int i = 0; i < size_dynamic; ++i)
        printf("%d floors, %.2lf m, %.2lf m - spire, %s, %s\n",
               array_dynamic[i].num_of_floors, array_dynamic[i].height_general, array_dynamic[i].height_spire,
               array_dynamic[i].design, array_dynamic[i].region);

    return 0;
}
