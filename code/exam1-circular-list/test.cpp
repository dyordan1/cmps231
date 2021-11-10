#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "circular-list.h"
using namespace std;

const bool YOUVE_WRITTEN_THESE_BEFORE_RIGHT = true;

// You will likely benefit from referencing 10-linked-list/ while adding
// these tests. You don't need to be nearly as extensive - but you will be
// evaluated on your ability to design good tests.
TEST_CASE("Write Me")
{
    REQUIRE(YOUVE_WRITTEN_THESE_BEFORE_RIGHT);
}

TEST_CASE("CircularList has no size on construction")
{
    CircularList<int> list;
    REQUIRE(list.size() == 0);
    REQUIRE(list.is_empty() == true);
}

TEST_CASE("You can clear an empty list, and nothing blows up")
{
    CircularList<int> list;
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list.is_empty() == true);
}

TEST_CASE("After insert, the size should be updated properly")
{
    CircularList<int> list;
    list.push(5);
    list.push(10);
    REQUIRE(list.is_empty() == false);
    REQUIRE(list.size() == 2);

    // while we are at it, make sure clear does it's job...
    list.clear();
    REQUIRE(list.is_empty() == true);
    REQUIRE(list.size() == 0);
}

TEST_CASE("Front returns copy - list contents cannot change")
{
    CircularList<int> list;

    list.push(5);

    int v = *list.begin();
    v = 42;
    REQUIRE(*list.begin() == 5);

    REQUIRE(list.size() == 1);
}

TEST_CASE("Pop back removes items from list and updates length")
{
    CircularList<int> list;
    list.push(5);
    list.push(10);
    list.push(15);
    list.push(20);
    // 5, 10, 15, 20
    REQUIRE(list.size() == 4);
    list.remove(list.begin());
    list.remove(list.begin());
    // expect 15, 20
    REQUIRE(*list.begin() == 15);
    REQUIRE(list.size() == 2);
}

TEST_CASE("Clear should remove all elements")
{
    CircularList<int> list;
    list.push(5);
    list.push(10);
    list.push(15);
    list.push(20);
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list.is_empty() == true);
}

/////////////////////////////////////////////////////////
// Destructor test
/////////////////////////////////////////////////////////
// The following test is designed to ensure that the
// destructor of each node is always called when a CircularList
// goes out of scope.  This is tricky though... we need
// to introduce a "spy", an object that can keep track
// of of how many times destructors are called.
class Spy
{
public:
    Spy()
    {
        // Spy is a useless object, it's just a placeholder
        // with destructor counting.
    }
    ~Spy()
    {
        Spy::destructor_count++;
    }

    static int destructor_count;
};

// Initialize the static counter.
int Spy::destructor_count = 0;

// We will call this function inside our test.
// Remember, we know CircularList's destructor will be called,
// there is no need to test whether C++ is correct.
// What we are worried about is if the destructor
// of the ELEMENT is called.
void dummy_function()
{
    CircularList<Spy> spies;
    spies.push(Spy());
    spies.push(Spy());
    return;
}

TEST_CASE("Destructor should be called on all nodes")
{

    dummy_function();

    // Dummy function inserts two spies, so why do we expect
    // that the destructor would get called 6 times?
    REQUIRE(Spy::destructor_count == 6);
    // - Each spy object is constructed and passed BY COPY inside
    //   dummy function to push_front, these objects get destructed as soon
    //   as the call is completed (2).
    // - Inside push_front, we pass the "data" by copy to the node constructor,
    //   and when push_front returns, the objects passed to it (by copy) are
    //   destructed (4).
    // - Finally, when the list of spies goes out of scope,
    //   list deletes each spy - hopefully (6).

    // Note, we could have also put a static counter in the node class, and
    // had the node's destructor decrement the counter.  This would allow
    // us to test without a fake spy object - but it's not a good idea, since
    // that would mean our list nodes would always carry this overhead in
    // real actual programs...

    // As an exercise, see if you can build a test case that
    // proves that the destructor of the node is always called
    // when pop_front, pop_back, and remove are called.  Hint, re-use
    // the same Spy class - but reset the static counter to keep things
    // simple in your test cases.
}

TEST_CASE("Push inserts at end and updates length")
{
    CircularList<int> list;
    list.push(5);
    list.push(10);
    list.push(15);
    list.push(20);
    list.push(25);
    list.push(30);
    REQUIRE(list.size() == 6);
}

TEST_CASE("Find")
{
    CircularList<int> list;
    list.push(5);
    list.push(10);
    list.push(15);
    list.push(20);
    list.push(25);
    list.push(30);

    REQUIRE(list.find(5) == list.begin());

    auto middle = list.begin();
    middle.forward();
    middle.forward();
    middle.forward();
    REQUIRE(list.find(20) == middle);

    auto end = list.begin();
    end.back();
    REQUIRE(list.find(30) == end);
}

TEST_CASE("Push can insert into empty list")
{
    CircularList<int> list;
    list.push(5);
    REQUIRE(list.size() == 1);
    REQUIRE(*list.begin() == 5);
}

/////////////////////////////////////////////////
// Iterator tests
/////////////////////////////////////////////////
TEST_CASE("Begin on empty list is invalid iterator.")
{
    CircularList<int> list;
    REQUIRE(list.begin().valid() == false);
}

TEST_CASE("Begin on non-empty list is valid iterator.")
{
    CircularList<int> list;
    list.push(5);
    REQUIRE(list.begin().valid() == true);
}

TEST_CASE("Next on only node produces same iterator")
{
    CircularList<int> list;
    list.push(5);
    auto it = list.begin();
    it.forward();
    REQUIRE(it == list.begin());
}

TEST_CASE("Next on node with next produces valid iterator")
{
    CircularList<int> list;
    auto invalid = list.begin();
    list.push(5);
    list.push(10);
    list.push(15);
    list.push(20);

    auto it = list.begin();
    REQUIRE(it.valid() == true);
    REQUIRE(it.data() == 5);

    it.forward();
    REQUIRE(it.valid() == true);
    REQUIRE(it.data() == 10);

    it.forward();
    REQUIRE(it.valid() == true);
    REQUIRE(it.data() == 15);

    it.forward();
    REQUIRE(it.valid() == true);
    REQUIRE(it.data() == 20);

    it.forward();
    REQUIRE(it == list.begin());

    // Let's test that a proper exception is thrown
    // if we try to move forward on an invalid iterator.
    CHECK_THROWS_AS(invalid.forward(), std::out_of_range);
    // or get it's data...
    CHECK_THROWS_AS(invalid.data(), std::out_of_range);
}

// When you are building a template class, ALWAYS test with at least
// another data type to ensure that the template has been constructed
// correctly.  It's easy to miss a T and replace it with int!
TEST_CASE("Test iteration forwards")
{
    CircularList<double> list;
    for (int i = 0; i < 10; i++)
    {
        list.push(3.0 + i * 0.01);
    }
    auto it = list.begin();
    int i = 0;
    double last_val = 3.09;
    do
    {
        last_val = it.data();
        REQUIRE(last_val - (3.0 + i * 0.01) < 0.01);
        it.forward();
        i++;
    } while (it != list.begin());
    REQUIRE(last_val - 3.09 < 0.01);
}

TEST_CASE("Test iteration backwards")
{

    CircularList<double> list;
    for (int i = 0; i < 10; i++)
    {
        list.push(3.0 + i * 0.01);
    }
    auto it = list.begin();
    it.back();
    int i = 9;
    double last_val = 3.09;
    do
    {
        last_val = it.data();
        REQUIRE(last_val - (3.0 + i * 0.01) < 0.01);
        it.back();
        i--;
    } while (it != list.begin());
    REQUIRE(last_val - 3.01 < 0.01);
}

TEST_CASE("Test insertion")
{
    CircularList<int> list;
    list.push(1);
    list.push(2);
    list.push(3);
    list.push(4);

    auto it = list.begin();
    // Test that the value can be added at the head
    list.insert(it, 0);
    int v = 0;

    auto i = list.begin();
    i.back();
    do
    {
        REQUIRE(i.data() == v);
        i.forward();
        v++;
    } while (i != list.begin());

    // Test that the value can be added in the "middle".
    // STL invalidates the iterator if the list has changed, we didn't - but
    // we certainly need to get a new one to be safe - as the data
    // in the list changed.
    it = list.begin();   // 1
    it.back();           // 0
    it.back();           // 4
    it.back();           // 3
    it.back();           // 2
    list.insert(it, 42); // insert before 2

    it = list.begin();
    it.back();
    REQUIRE(it.data() == 0);
    it.forward();
    REQUIRE(it.data() == 1);
    it.forward();
    REQUIRE(it.data() == 42);
    it.forward();
    REQUIRE(it.data() == 2);
    it.forward();
    REQUIRE(it.data() == 3);
    it.forward();
    REQUIRE(it.data() == 4);
    it.forward();
}
