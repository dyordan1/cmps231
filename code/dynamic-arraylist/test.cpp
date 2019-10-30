#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "array-list.h"
#include <stdexcept>
using namespace std;

TEST_CASE("Constructor initializes the array correctly")
{
    ArrayList<int> al;
    REQUIRE(al.length() == 0);
}

TEST_CASE("Appending changes length (int)")
{
    ArrayList<int> al;
    al.append(5);
    al.append(10);
    REQUIRE(al.length() == 2);
}

TEST_CASE("Appending grows list as needed")
{
    ArrayList<int> al;
    for ( int i =0 ; i < 1000; i++ ) {
        al.append(i+1);    
    }
    
    REQUIRE(al.length() == 1000);
}




TEST_CASE("Appending changes length")
{
    ArrayList<int> al;
    al.append(5);
    al.append(10);
    REQUIRE(al.length() == 2);
}

TEST_CASE("Prepending changes length")
{
    ArrayList<int> al;
    al.prepend(5);
    al.prepend(2);
    REQUIRE(al.length() == 2);
}

TEST_CASE("Get returns the correct value")
{
    ArrayList<int> al;
    al.prepend(5);
    al.prepend(2);
    REQUIRE(al.get(1) == 5);
}


TEST_CASE("Get throws exception if index is less than 0")
{
    ArrayList<int> al;
    al.prepend(5);
    al.prepend(10);
    CHECK_THROWS_AS(al.get(-1), out_of_range);
}
