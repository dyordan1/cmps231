#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "queue.h"
#include <stdexcept>
using namespace std;

TEST_CASE("Constructor initializes the queue correctly")
{
    queue q;
    REQUIRE(q.is_empty() == true);
    REQUIRE(q.is_full() == false);
}

TEST_CASE("Enqueue makes queue not empty")
{
    queue q;
    q.enqueue(5);
    REQUIRE(q.is_empty() == false);
    
    // Clearly shouldn't be full now...
    REQUIRE(q.is_full() == false);
}

TEST_CASE("Enqueue can be called repeatedly")
{
    queue q;
    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(20);
    REQUIRE(q.is_empty() == false);
    REQUIRE(q.is_full() == false);
}

TEST_CASE("Dequeue returns value and removes")
{
    queue q;
    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(20);
    int v1 = q.dequeue();
    int v2 = q.dequeue();
    
    REQUIRE(v1 == 5);
    REQUIRE(v2 == 10);
    REQUIRE(q.is_empty() == false);
    REQUIRE(q.is_full() == false);
}

TEST_CASE("Enqueue wraps around back of queue")
{
    // Note, to keep in line with the slides, I used a ridiculuous size for the array
    // that implements the queue... 6!
    queue q;
    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(20);
    int v1 = q.dequeue();
    int v2 = q.dequeue();
    
    REQUIRE(v1 == 5);
    REQUIRE(v2 == 10);
    
    q.enqueue(25);
    q.enqueue(30);
    q.enqueue(35);
    REQUIRE(q.is_empty() == false);
    REQUIRE(q.is_full() == false);
}

TEST_CASE("Dequeue will wrap around array to return proper values.")
{
    // Note, to keep in line with the slides, I used a ridiculuous size for the array
    // that implements the queue... 6!
    queue q;
    q.enqueue(5);
    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(20);
    int v1 = q.dequeue();
    int v2 = q.dequeue();
    
    REQUIRE(v1 == 5);
    REQUIRE(v2 == 10);
    
    q.enqueue(25);
    q.enqueue(30);
    q.enqueue(35);
    q.enqueue(40);
    
    REQUIRE(q.is_full() == true);
    
    int v3 = q.dequeue();
    int v4 = q.dequeue();
    int v5 = q.dequeue();
    int v6 = q.dequeue();
    int v7 = q.dequeue();
    int v8 = q.dequeue();
    
    
    
    REQUIRE(v3 == 15);
    REQUIRE(v4 == 20);
    REQUIRE(v5 == 25);
    REQUIRE(v6 == 30);
    REQUIRE(v7 == 35);
    REQUIRE(v8 == 40);
    
    REQUIRE(q.is_empty() == true);
    REQUIRE(q.is_full() == false);
}



