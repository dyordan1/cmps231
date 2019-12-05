#include <iostream>
#include <queue> // Good for the radix sort...
#include <cmath> // Used in radix finding...
using namespace std;

void swap (int values[], int i, int j) {
    int tmp = values[i];
    values[i] = values[j];
    values[j] = tmp;
}
int index_of_min(int values[], int start, int end) {
    int min = start;
    for ( int i = start+1; i <= end; i++ ) {
        if ( values[i] < values[min])min = i;
    }
    return min;
}


void selection_sort(int values[], int n) {
    for ( int i = 0; i < n; i++ ) {
        int min = index_of_min(values, i, n-1);
        swap(values, i, min);
    }
    return;
}

void bubble_sort(int values[], int n) {
    // The sorted portion of the list is the back part...
    // At each turn of the outer loop, we are placing a single value
    // in the sorted portion of the list, by bubbling it up the index
    // list.
    for (int i = 1; i < n; i++) {
        // The (n-i) part is key here.  As i increases, this inner
        // loop is examining less and less of the array - as the n-i valued
        // index is reduced.  Eventually, n-i will converge to 0 and there is 
        // no longer any need to bubble up.
        bool swapped = false;
        for ( int j = 0; j < n-i; j++ ) {
            if ( values[j] > values[j+1]) {
                swap(values, j, j+1);
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

void insert(int values[], int index) {
    // Specialized insert.  The value we are inserting 
    // is found at index.  The list we are inserting into
    // is SORTED, and always starts at index 0, and (currently)
    // ends at index "index-1".  This allows us to simply slide
    // the value at index from right to left until in place.
    for ( int i = index-1; i >= 0; i--) {
        // first time around loop, i+1 == index.
        // if we swap, then i is reduced to continue
        // moving left.
        if ( values[i] > values[i+1]) {
            swap(values, i, i+1);
        } else {
            // It's a sorted list, so if the value sliding to the left
            // is larger than the value to the left of it, it's also
            // larger than ALL the value to the left - no need to continue
            // any further.
            return;
        }
    }
}

void insertion_sort(int values[], int n) {
    // Sorted list is on left side, unsorted on right.
    // We consider the sorted list to already contain one element...
    for ( int i = 1; i < n; i++ ) {
        insert(values, i);
    }
}
int digit(int value, int radix) {
    int div = pow(10, radix);
    return value / div % 10;
}

void radix_sort(int values[], int n, int radix){
    // Left as Lab Exercise.
    // Hint:  Make use of STL queues for you buckets (at least).
}


/*******************
Heap Sort
********************/
int left(int i) {
    return 2 * i + 1;
}
int right(int i) {
    return 2 * i + 2;
}
int parent(int i) {
    return (i-1)/2;
}
void reheap(int a[], int cp, int endIndex) {
    // if left or right is greater, than swap with largest
    // initialize as one less than the current value, 
    // this way if the left or right is not present, it will be ignored
    int lvalue = a[cp]-1; 
    int rvalue = a[cp]-1;
     
    // get the left and right values (if they exist)
    if ( left(cp) <= endIndex ) lvalue = a[left(cp)];
    if ( right(cp) <= endIndex ) rvalue = a[right(cp)];
     
    // if the left value is greater than the current, 
    // and it is the biggest of the children
    if ( lvalue > a[cp] && lvalue >= rvalue ) {
        swap (a,  cp, left(cp) );
        reheap(a, left(cp), endIndex);
    }
    // if the right value is greater than the current, 
    // and it is the biggest of the children
    else if ( rvalue > a[cp] && rvalue >= lvalue ) {
        swap (a, cp, right(cp) );
        reheap(a, right(cp), endIndex);
    }
    else {
        return;
    }
}
void heap_sort(int heap_sort[], int n) {
    // first make a an heap by calling reheap on all elements
    for ( int i = n-1; i >= 0; i-- ) {
        reheap(heap_sort, i, n-1);
    }
    // Now sort...
    for ( int i =n-1; i > 0; i-- ) {
        swap(heap_sort, 0, i);
        reheap(heap_sort, 0, i-1);
    }
}
