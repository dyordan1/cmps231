#include "queue.h"

using namespace std;

queue:: queue() {
    count  =0;
    front = 0;
    back = 0;
    
}
void queue:: enqueue(int value) {
    if (is_full()) {
        throw length_error("Out of room in queue");
    }
    data[back] = value;
    back++;
    count++;
    if (back == QMAX_SIZE) {
        back = 0;
    }
}

int queue:: dequeue() {
    if (is_empty()) {
        throw length_error("No contents of queue");
    }
    int value = data[front];
    front++;
    count --;
    if(front == QMAX_SIZE) {
        front = 0;
    }
    return value;
}
bool queue:: is_full() {
    return count == QMAX_SIZE;
}
bool queue:: is_empty() {
    return count == 0;
}