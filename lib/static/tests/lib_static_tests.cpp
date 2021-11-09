//
// Created by ivan on 09.11.2021.
//
#include <gtest/gtest.h>

extern "C" {
#include "lib.h"
#include <stdio.h>
#include <time.h>
}
TEST(SORT, size_2) {
int array[2] = {1, 0};

int *sorted_array = my_sort(array, 2);

EXPECT_EQ(test(sorted_array, 2), 0);
}

TEST(SORT, size_3) {
int array[3] = {1, 2, 0};

int *sorted_array = my_sort(array, 3);

EXPECT_EQ(test(sorted_array, 3), 0);
}

TEST(SORT, size_4) {
int array[4] = {2, 0, 1, 3};

int *sorted_array = my_sort(array, 4);

EXPECT_EQ(test(sorted_array, 4), 0);
}

TEST(SORT, size_100000) {
int array[100000];
srand(time(NULL));
for (int i = 0; i < 100000; ++i)
array[i] = rand() % 100000;

int *sorted_array = my_sort(array, 100000);

EXPECT_EQ(test(sorted_array, 100000), 0);
}

TEST(SORT, size_99999) {
int array[99999];
srand(time(NULL));
for (int i = 0; i < 99999; ++i)
array[i] = rand() % 100000;

int *sorted_array = my_sort(array, 99999);

EXPECT_EQ(test(sorted_array, 99999), 0);
}
