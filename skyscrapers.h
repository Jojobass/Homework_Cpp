#pragma once
typedef struct Skyscraper {
    int num_of_floors;
    double height_general;
    double height_spire;
    char *design;
    char *region;
} Skyscraper;

void swap(Skyscraper *x, Skyscraper *y);

void sort_skyscrapers(Skyscraper arr[], int size, int mode);

Skyscraper add_skyscraper(int size_dynamic);

Skyscraper *fill(Skyscraper arr[]);