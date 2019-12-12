#include <iostream>
#include <queue> // Good for the radix sort...
#include <cmath> // Used in radix finding...
using namespace std;
const int MAX = 10000;


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


void merge(int a[], int start1, int end1, int start2, int end2) {
    int tmp[MAX];  // will temporarily hold the merged array
    int i = 0;  // index used to fill up tmp array
    int first = start1;  // index of the original first element
    int left = start1;   // index to iterate through left array
    int right = start2;  // index to iterate through right array
     
    // while there are element in both the left an right array
    while ( left <= end1 && right <= end2 ) {
        // if the element in the left is smaller than the one in the right, 
        // put the element in the left array into tmp
        if ( a[left] < a[right] ) {
            tmp[i++] = a[left++];
        }
        // otherwise, place the element in the right array into tmp
        else {
            tmp[i++] = a[right++];
        }
    }
     
    // now there should be items remaining in one of the lists...
    // only one of these two loops will run (since one is already empty)
    while ( left <= end1 ) {
        tmp[i++] = a[left++];
    }
    while ( right <= end2 ) {
        tmp[i++] = a[right++];
    }
     
     
    // now copy the array we just put together in tmp into the original array.
    int j = 0; 
    for ( int i = first; i <= end2; i++ ) {
        a[i] = tmp[j++];
    }
     
     
}
 
void _mergeSort(int a[], int start, int end) {
    // check for base case
    if ( start >= end) {
        // there is only one element, its sorted, return.
        // (a list that has one element is sorted, by definition)
        return;
    }
    else {
        // divide the problem by splitting the array in half
        int middle = (start + end)/2; // find middle portion
        _mergeSort(a, start, middle); // sort "left" half by merge sort
        _mergeSort(a, middle+1, end); // sort "right hald by merge sort
        merge ( a, start, middle, middle+1, end); // merge the two (sorted) halves together
    }
}
 
 
void merge_sort(int values[], int n) {
    // call recursive merge sort
    _mergeSort(values, 0, n-1);
}

int Split(int a[], int first, int last) {
    // use the first value as the pivot.
    // this is a good chocie if the list is assumed to be random
    // better choices are possible
    int splitValue = a[first];
     
    int f = first;  // save the index of the first element...
    first++;
     
    // we have two indices, first and last.  first moves to the right, last moves
    // to the left.  When they meet, we are done...
    do {
        // move "first" to the right until the value in first is greater than the 
        // pivot value or first == last
        while ( first <= last && a[first] <= splitValue ) {
            first++;
        }
        // move "last" to the left until the value in last is less than the pivot value
        while ( first <= last && a[last] > splitValue ) {
            last--;
        }
        // if first and last haven't met, it means first and last can be swapped
        // so they end up on the correct "side" of the pivot
        if ( first < last ) {
            swap(a, first++, last--);
        }
    } while ( first <= last );
     
    int splitPoint = last;
    swap(a, f, splitPoint); // swap the first with the pivot so a new pivot will be
                            // selected next time...
    return splitPoint;
     
}
 
void _quickSort(int a[], int first, int last) {
    // quick sort the list that starts at element "first" and ends at element
    // "last"
     
    // if first is not less than last, then the list is empty, return immediately
    if ( first < last ) {
        // split the list according to a pivot value (pivot value is 
        // decided by the Split function itself
        int pivot = Split(a, first, last);
        _quickSort(a, first, pivot-1);  // quick sort the list to the left of the pivot
        _quickSort(a, pivot+1, last);   // quick sort the list to the right of the pivot
    }
}
 
void quick_sort(int values[], int n) {
    // call the recursive quick sort function
    _quickSort(values, 0, n-1);
     
}