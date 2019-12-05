#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "sorting.h"

using namespace std;

const int SIZE = 10;
int _numbers[] = {5, 293, 395, 12, 345, 182, 48, 94, 42, 86};


void initialize(int values[]) {
    for ( int i = 0 ; i < SIZE; i++ ) {
        values[i] = _numbers[i];
    }
}

bool is_in(int values[], int value) {
    for ( int i = 0; i < SIZE; i++) {
        if ( values[i] == value) return true;
    }
    return false;
}
bool is_in_order(int values[]) {
    for ( int i = 1; i < SIZE; i++) {
        if ( values[i-1] > values[i] ) return false;
    }
    return true;
}
bool all_in (int values[]) {
    for ( int i = 0; i < SIZE; i++) {
        if ( !is_in(values, _numbers[i]))  return false;
    }
    return true;
}

TEST_CASE("Selection Sort")
{
    int values [SIZE];
    initialize(values);
    selection_sort(values, SIZE);
    REQUIRE(all_in(values));
    REQUIRE(is_in_order(values));
}

TEST_CASE("Bubble Sort")
{
    int values [SIZE];
    initialize(values);
    bubble_sort(values, SIZE);
    REQUIRE(all_in(values));
    REQUIRE(is_in_order(values));
}

TEST_CASE("Insertion Sort")
{
    int values [SIZE];
    initialize(values);
    insertion_sort(values, SIZE);
    REQUIRE(all_in(values));
    REQUIRE(is_in_order(values));
}

TEST_CASE("Radix digit finder") {
    REQUIRE(digit(495, 0) == 5);
    REQUIRE(digit(495, 1) == 9);
    REQUIRE(digit(495, 2) == 4);
    REQUIRE(digit(5, 0) == 5);
    REQUIRE(digit(5, 1) == 0);
    REQUIRE(digit(5, 2) == 0);
}
TEST_CASE("Radix Sort")
{
    int values [SIZE];
    initialize(values);
    //radix_sort(values, SIZE, 3);
    REQUIRE(all_in(values));
    //REQUIRE(is_in_order(values));
}

TEST_CASE("Heap Sort")
{
    int values [SIZE];
    initialize(values);
    heap_sort(values, SIZE);
    REQUIRE(all_in(values));
    REQUIRE(is_in_order(values));
}