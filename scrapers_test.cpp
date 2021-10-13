#include <gtest/gtest.h>
extern "C"{
    #include "skyscrapers.h"
}

//тесты на заполнения массива 6 стандартными небоскребами
TEST(FILL, Assert_fill_1) {
Skyscraper array[6];
fill(array);
EXPECT_EQ(array[0].height_spire, 12.3);
}

TEST(FILL, Assert_fill_2) {
Skyscraper array[6];
fill(array);
EXPECT_EQ(array[5].height_spire, 3.6);
}
//тесты на сортировку по назначению
TEST(SORT, Assert_sort_11) {
Skyscraper array[6];
fill(array);
sort_skyscrapers(array, 6, 1);
EXPECT_STREQ(array[0].design, "Office");
EXPECT_STREQ(array[1].design, "Office");
EXPECT_STREQ(array[2].design, "Office");
}

TEST(SORT, Assert_sort_12) {
Skyscraper array[6];
fill(array);
sort_skyscrapers(array, 6, 1);
EXPECT_STREQ(array[3].design, "Hotel");
EXPECT_STREQ(array[4].design, "Hotel");
EXPECT_STREQ(array[5].design, "Hotel");
}
//тесты на сортировку по региону
TEST(SORT, Assert_sort_21) {
Skyscraper array[6];
fill(array);
sort_skyscrapers(array, 6, 2);
EXPECT_STREQ(array[0].region, "Europe");
EXPECT_STREQ(array[1].region, "Europe");
}

TEST(SORT, Assert_sort_22) {
Skyscraper array[6];
fill(array);
sort_skyscrapers(array, 6, 2);
EXPECT_STREQ(array[2].region, "Asia");
EXPECT_STREQ(array[3].region, "Asia");
}

TEST(SORT, Assert_sort_23) {
Skyscraper array[6];
fill(array);
sort_skyscrapers(array, 6, 2);
EXPECT_STREQ(array[4].region, "Middle-East");
EXPECT_STREQ(array[5].region, "Middle-East");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}