cmake_minimum_required(VERSION 3.7)

project(Homework1)

add_library(skyscrapers STATIC skyscrapers.c)

add_executable(main main.c)
target_link_libraries(main skyscrapers)

enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(scrapers_test scrapers_test.cpp)
target_link_libraries(scrapers_test ${GTEST_LIBRARIES} skyscrapers pthread)
