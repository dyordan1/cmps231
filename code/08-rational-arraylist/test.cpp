#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "array-list.h"
#include "rational.h"
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

TEST_CASE("Appending changes length (rational)")
{
    ArrayList<Rational> al;
    al.append(Rational(5, 10));
    al.append(Rational(7, 10));
    REQUIRE(al.length() == 2);
}

TEST_CASE("Prepending changes length")
{
    ArrayList<Rational> al;
    al.prepend(Rational(5, 8));
    al.prepend(Rational(2, 1));
    REQUIRE(al.length() == 2);
}

TEST_CASE("Get returns the correct value")
{
    ArrayList<Rational> al;
    al.prepend(Rational(5, 8));
    al.prepend(Rational(2, 1));
    REQUIRE(al.get(1) == Rational(5, 8));
}

TEST_CASE("Indexing returns the correct value")
{
    ArrayList<Rational> al;
    al.prepend(Rational(5, 8));
    al.prepend(Rational(2, 1));
    REQUIRE(al[1] == Rational(5, 8));
}

TEST_CASE("Indexing allows setting the value")
{
    ArrayList<Rational> al;
    al.prepend(Rational(5, 8));
    al.prepend(Rational(2, 1));
    al[1] = Rational(14, 17);
    REQUIRE(al[1] == Rational(14, 17));
}

TEST_CASE("Indexing permitted with array syntax")
{
    ArrayList<Rational> al;
    al.prepend(Rational(5, 8));
    al.prepend(Rational(2, 1));
    al[1] = Rational(14, 17);

    REQUIRE(al[1] == Rational(14, 17));
    REQUIRE(al[0] == Rational(2, 1));
}

TEST_CASE("Get throws exception if index is less than 0")
{
    ArrayList<int> al;
    al.prepend(5);
    al.prepend(10);
    CHECK_THROWS_AS(al.get(-1), out_of_range);
}

TEST_CASE("Find returns -1 if not found")
{
    ArrayList<Rational> al;
    al.prepend(Rational(2, 3));
    al.prepend(Rational(2, 5));
    REQUIRE(al.find(Rational(5, 6)) == -1);
}

TEST_CASE("Find returns the correct index for the given value")
{
    ArrayList<Rational> al;
    al.append(Rational(2, 3));
    al.append(Rational(2, 5));
    al.append(Rational(6, 5));
    al.append(Rational(9, 5));
    REQUIRE(al.find(Rational(2, 5)) == 1);
}