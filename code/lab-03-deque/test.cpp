#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "deque.h"
#include <stdexcept>
using namespace std;

TEST_CASE("Constructor initializes correctly")
{
    Deque d;
    REQUIRE(d.is_empty() == true);
    REQUIRE(d.is_full() == false);
}

TEST_CASE("Push back adds correctly, and protects against overflow")
{
    Deque d;
    for (int i = 0; i < Deque::CAPACITY; i++)
    {
        d.push_back(i);
    }
    REQUIRE(d.is_empty() == false);
    REQUIRE(d.is_full() == true);
    CHECK_THROWS_AS(d.push_back(42), length_error);

    int v = d.pop_front();
    REQUIRE(v == 0);
}

TEST_CASE("Push front adds correctly, and protects against overflow")
{
    Deque d;
    for (int i = 0; i < Deque::CAPACITY; i++)
    {
        d.push_front(i);
    }
    REQUIRE(d.is_empty() == false);
    REQUIRE(d.is_full() == true);
    CHECK_THROWS_AS(d.push_front(42), length_error);

    int v = d.pop_front();
    REQUIRE(v == 99);
}

TEST_CASE("Pop front removes correctly, and protects against underflow")
{
    Deque d;

    d.push_front(0);
    d.push_front(1);
    d.push_back(2);
    d.push_back(3);

    REQUIRE(d.pop_front() == 1);
    REQUIRE(d.pop_front() == 0);
    REQUIRE(d.pop_front() == 2);
    REQUIRE(d.pop_front() == 3);
    REQUIRE(d.is_empty() == true);
    CHECK_THROWS_AS(d.pop_front(), length_error);
}

TEST_CASE("Pop back removes correctly, and protects against underflow")
{
    Deque d;

    d.push_front(0);
    d.push_front(1);
    d.push_back(2);
    d.push_back(3);

    REQUIRE(d.pop_back() == 3);
    REQUIRE(d.pop_back() == 2);
    REQUIRE(d.pop_back() == 0);
    REQUIRE(d.pop_back() == 1);
    REQUIRE(d.is_empty() == true);
    CHECK_THROWS_AS(d.pop_back(), length_error);
}

TEST_CASE("Handles back wrap around")
{
    Deque d;

    for (int i = 0; i < Deque::CAPACITY; i++)
    {
        d.push_back(i);
    }
    REQUIRE(d.is_full() == true);
    d.pop_front();
    d.pop_front();
    REQUIRE(d.is_full() == false);
    d.push_back(200);
    d.push_back(42);
    REQUIRE(d.pop_back() == 42);
    REQUIRE(d.pop_back() == 200);
    REQUIRE(d.pop_back() == 99);
}

TEST_CASE("Handles back wrap around, front push")
{
    Deque d;

    for (int i = 0; i < Deque::CAPACITY; i++)
    {
        d.push_back(i);
    }
    REQUIRE(d.is_full() == true);
    d.pop_front(); // removes 0
    d.pop_front(); // removes 1
    REQUIRE(d.is_full() == false);
    d.push_front(200);
    d.push_front(42);
    REQUIRE(d.pop_front() == 42);
    REQUIRE(d.pop_front() == 200);
    REQUIRE(d.pop_front() == 2);
}

TEST_CASE("Handles pop front wrap around")
{
    Deque d;

    for (int i = 0; i < Deque::CAPACITY; i++)
    {
        d.push_back(i);
    }
    // 0....99
    for (int i = 0; i < Deque::CAPACITY - 2; i++)
    {
        d.pop_front();
    }
    // ...... 98, 99.

    REQUIRE(d.is_full() == false);
    for (int i = 0; i < 5; i++)
    {
        d.push_back(200 + i);
    }
    // 200, 201, ... 204.............. 98, 99.
    d.pop_front(); // removes 98
    d.pop_front(); // removes 99
    d.pop_front(); // removes 200
    REQUIRE(d.pop_front() == 201);
    REQUIRE(d.pop_back() == 204);
}