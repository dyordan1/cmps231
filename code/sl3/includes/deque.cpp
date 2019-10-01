#include "deque.h"
#include <stdexcept>
using namespace std;

Deque::Deque()
{
    // Initialize the contents of your list.
    count = 0;
    back =0;
    front = 0;
}

void Deque::right(int &index){
    index++;
    if ( index == CAPACITY) {
        index = 0;
    }
}
void Deque::left(int &index) {
    index--;
    if (index < 0) {
        index = CAPACITY-1;
    }
}


void Deque::push_back(int value)
{
    if ( is_full() ) {
        throw length_error("deque is full");
    }
    data[back] = value;
    right(back);
    count++;
}
void Deque::push_front(int value)
{
    if ( is_full() ) {
        throw length_error("deque is full");
    }
    left(front);
    data[front] = value;
   
    count++;
}
int Deque::pop_back()
{
    if (is_empty()) {
        throw length_error("No contents of queue");
    }
    // Tricky..back points to the next location where
    // something should be added.  So we need the previous
    // location.  But remember, this is a circular array - so
    // back - 1 might trigger wrapping around to the array boundary!
    // So.. move back first - and return the value found there.
    left(back);
    int value = data[back];
    
    count--;

    return value;
}
int Deque::pop_front()
{
    if (is_empty()) {
        throw length_error("No contents of queue");
    }
    int value = data[front];
    right(front);
    count--;

    return value;
}

bool Deque::is_full() const
{
    return count == CAPACITY;
}

bool Deque::is_empty() const
{
    return count == 0;
}
