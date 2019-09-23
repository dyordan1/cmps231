#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "sorted-list.h"
#include <stdexcept>
using namespace std;

TEST_CASE("Constructor initializes the array correctly")
{
    SortedList al;
    REQUIRE(al.length() == 0);
}

TEST_CASE("Appending changes length")
{
    SortedList al;
    al.insert(5);
    al.insert(3);
    al.insert(9);
    al.insert(6);
    REQUIRE(al.length() == 4);
    
    REQUIRE(al.get(0) == 3);
    REQUIRE(al.get(1) == 5);
    REQUIRE(al.get(2) == 6);
    REQUIRE(al.get(3) == 9);
}
