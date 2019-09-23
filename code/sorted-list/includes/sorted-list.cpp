#include "sorted-list.h"
#include <stdexcept>

SortedList::SortedList()
{
    // Initialize the contents of your list.
    count = 0;
}

void SortedList::insert(int value) {
    if (count >= CAPACITY) {
        throw std::length_error("Out of room");
    }
    for (int i = 0; i < count; i++ ) {
        if ( data[i] > value) {
            insertAt(value, i);
            return;
        }
    }
    insertAt(value, count);
}

// private
void SortedList::insertAt(int value, int index){
   
    for ( int i = count; i > index; i-- ) {
        data[i] = data[i-1];
    }
    data[index] = value;
    count++;
    
}

void SortedList::remove(int index) {
    if ( index < 0 || index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    for ( int i = index; i < count-1; i++ ) {
        data[i] = data[i+1];
    }
    count--;
    
}
int SortedList::get(int index) const
{
    if ( index < 0 || index >= count) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}
int SortedList::find(int value) const
{
    for ( int i = 0; i < count; i++ ) {
        if ( data[i] == value) {
            return i;
        } else if ( data[i] > value) {
            return -1;
        }
    }
    return -1;
}

int SortedList::length() const
{
    return count;
}
