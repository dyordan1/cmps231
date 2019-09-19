#include "queue.h"
using namespace std;

queue:: queue() {
    count = 0;
    front = 0;
    back = 0;
}
void queue:: enqueue(int value) {
    if ( is_full()) {
       throw std::length_error("queue has reached capacity and cannot be added to.");
    }
    data[back] = value;
    count++;
    back++;
    if ( back >= QMAX_SIZE) back = 0;
}

int queue:: dequeue() {
    if ( is_empty()) {
       throw std::length_error("queue has no elements.");
    }
    int value = data[front];
    count--;
    front++;
    if ( front >= QMAX_SIZE) front = 0;
    return value;
}
bool queue:: is_full() {
    return count >= QMAX_SIZE;
}
bool queue:: is_empty() {
    return count <= 0;
}