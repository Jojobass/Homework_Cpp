#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skyscrapers.h"

//меняет местами 2 элемента массива с небоскребами
void swap(Skyscraper *x, Skyscraper *y) {
    Skyscraper buffer = *x;
    *x = *y;
    *y = buffer;
}

//сортирует массив небоскребов (mode: 1 - по назначению, 2 - по региону)
void sort_skyscrapers(Skyscraper arr[], int size, int mode) {
    if(arr == NULL || size < 3) return;
    //текущий элемент
    for (int i = 0; i < size - 2; ++i) {
        //рассматриваемый элемент
        for (int j = i + 1; j < size; ++j) {
            //если совпадает, то следующий за текущим меняется с ним, текущий передвигается на 1 вперед
            if ((mode == 1 && strcmp(arr[j].design, arr[i].design) == 0) ||
                (mode == 2 && strcmp(arr[j].region, arr[i].region) == 0)) {
                if (j != i + 1) swap(&arr[i + 1], &arr[j]);
                //текущий всегда в конце последовательности повторяющихся
                i++;
            }
        }
    }
}

//добавление небоскреба
Skyscraper add_skyscraper(int size_dynamic) {
    Skyscraper elem;
    elem.design = (char *) malloc(15 * sizeof(char));
    elem.region = (char *) malloc(15 * sizeof(char));
    //ввод характеристик небоскреба с консоли
    printf("array_dynamic[%d]:\n", size_dynamic);
    do {
        printf("Number of floors = ");
        scanf("%d", &elem.num_of_floors);
    } while (elem.num_of_floors < 1);
    do {
        printf("General height = ");
        scanf("%lf", &elem.height_general);
    } while (elem.height_general <= 0);
    do {
        printf("Height of spire = ");
        scanf("%lf", &elem.height_spire);
    } while (elem.height_spire < 0);

    printf("Design = ");
    scanf("%15s", elem.design);

    printf("Region = ");
    scanf("%15s", elem.region);

    return elem;
}

//заполнение начального массива на 6 небоскребов
Skyscraper *fill(Skyscraper arr[]) {
    Skyscraper first = {40, 130.5, 12.3, "Office", "Europe"};
    Skyscraper second = {41, 140, 15, "Office", "Middle-East"};
    Skyscraper third = {43, 150, 10, "Hotel", "Asia"};
    Skyscraper fourth = {50, 200, 12.6, "Office", "Asia"};
    Skyscraper fifth = {70, 350.2, 27.3, "Hotel", "Europe"};
    Skyscraper sixth = {52, 174.7, 3.6, "Hotel", "Middle-East"};
    arr[0] = first;
    arr[1] = second;
    arr[2] = third;
    arr[3] = fourth;
    arr[4] = fifth;
    arr[5] = sixth;
    return arr;
}