title: Pointers:  Review
---
class: center, middle, inverse
# Memory and Pointers
A Review

---
# Understanding memory
Every program must manage memory
- Variables are allocated in memory
- The OS allows programs to use any memory address **in the program's address space**

--


- Some programming languages have a *runtime* - which usually includes a **garbage collector** (GC)
 - Java, C#, JavaScript, Python, etc.
 - The runtime handles allocation on behalf of your code, at runtime.
 - The runtime does the bookeeping, and when all variables referencing the memory are out of scope, the memory is reclaimed.

.callout[
The "runtimes" for these languages are programs... written in C or C++.  C and C++ programs (and some others) are called **systems languages**, and do not have "runtimes".
]

---
# Systems languages
Many languages are "compiled" - meaning a compiler checks the code for syntax and outputs a "binary-like" program for execution.
- Compiled != Systems language
- Some languages (Java, C#) get compiled into an intermediate platform-agnostic binary.  The binary is executed by the "runtime".
- C and C++ get compiled into **native binary code** that executes on the CPU, with no abstraction layer.

Binary executables must manage their own memory, there is no "runtime" to save them!
- Some of the memory management is facilitated by the compiler.
- Other memory management must be 100% facilitated by the programmer.
---
# Compiler-managed memory
All programs have an entry point - `main`.
- `main` can contain local variables.
- Local variables always have a data type, and so at compile time, the C++ compiler **knows exactly how much memory** needs to be allocated when the function is called.

From main, it is likely you will call other functions:
- These functions may have local variables.
- These functions may have parameters.

.callout[
The key here is that the compiler know *exactly* how much memory needs to be allocated when a specific function is called.
]

---
# The (call) Stack

```c++
int sum (int a, int b) {
    int result = a + b;
    return result;
}
// This is a very silly function..
// With an awful name, to save space
int ss (int x, int y, int z) {
    int sqs[3] = {x*x, y*y, z*z}
    int tmp = sum(sqs[0], sqs[1]);
    int result = sum(tmp, sqs[2]);
    return result;
}

int main() {
    int x =  ss(3, 4, 5);
    int y =  ss(10, 200, 300);
    cout << sum(x, y) << endl;
}

```
How much memory should be allocated to hold the variables/parameters of `main`, `sum_of_squares`, and `sum`?

---
# The (call) Stack

.split-left[
```c++
int sum (int a, int b) {
    int result = a + b;
    return result;
}
// This is a very silly function..
// With an awful name, to save space
int ss (int x, int y, int z) {
    int sqs[3] = {x*x, y*y, z*z}
    int tmp = sum(sqs[0], sqs[1]);
    int result = sum(tmp, sqs[2]);
    return result;
}

int main() {
    int x =  ss(3, 4, 5);
    int y =  ss(10, 200, 300);
    cout << sum(x, y) << endl;
}

```
.callout[
Let's draw the stack for this.
]
]

.split-right[
- The compiler generates (assembly) code at each call point to allocate the "stack frame" for the function about to be called.
- The compiler also generates (assembly) code to de-allocate the "stack frame" on return.
- Each stack frame is allocated in a segment of memory called "the stack".
- The top of the stack is always the stack frame for the *current function*.
- Returning from a function just pops the stack frame!
]

---
# Sidebar:  Memory safety
- Local variables and parameters have addresses.  Their addresses are relative to the **top of the stack**.
- At runtime, there is nothing stopping a programmer's code from using these address locations unwisely.

```cpp
int ss (int x, int y, int z) {
    int sqs[3] = {x*x, y*y, z*z}
    int tmp = sum(sqs[0], sqs[1]);
    // Let's add a typo... where is
    // the 200th element of sqs?
    int result = sum(tmp, sqs[20]);
    return result;
}
```
--
.callout[
- Raw arrays in C++ are dangerous, because there is no bounds checking.
- The OS will (usually) stop you from writing into another program's memory
- The OS will **not** prevent you from clobbering your own stack!
]

---
# Dynamic memory (the Heap)
- Local variables and parameters have known address (offsets) at compiler time.
- Sometimes, we don't know how much space we need at compile time, only at runtime.
- For this, we have the **heap**.
- The heap is a different section of memory, managed by the programmer.

.callout[
The compiler can do very little for us with the heap.
]

---
# Allocating from the heap
- Heap allocation is done with the `new` keyword.
- The `new` keyword finds the next available position in the heap and returns it.
- It "returns it" by giving the programmer an **address** that can be used.
- The assembly code `new` gets compiled down to simply:
  - keeps track of where the heap is
  - finds the next available open slot fitting the size your request
  - returns the address for use.

```c++
int * intPtr = new int;         // finds 4 open bytes
double *doublePtr = new double; // finds 8 open bytes
char * str = new char[42];      // finds 42 open bytes
```
---
# Pointers and Addresses
```c++
int * intPtr = new int;         // finds 4 open bytes
double *doublePtr = new double; // finds 8 open bytes
char * str = new char[42];      // finds 42 open bytes
int x = 5;          // stack variable
int *localPtr = &x; // Gets the address of x
cout << localPtr << intPtr << doublePtr << endl;

localPtr = intPtr;
cout << localPtr << intPtr << doublePtr << endl;

intPtr = new int[100];
cout << localPtr << intPtr << doublePtr << endl;

intPtr[50] = 12;   // Pointers to arrays look just like arrays...
intPtr = &x;       // Uh oh....
```
.callout[
Let's draw all this out, and investigate the error a bit.
]
---
# Reference Operator
The `&` operator is used to get the *address* of a variable.
- You can *reference* anything.

```c++
int x = 5;

int * ptr1 = &x;
int * ptr2 = new int;
int * ptr3 = ptr1;  // ptr3 points to x
int * ptr4 = &ptr2; // what is this?
```

---
# Dereferencing Operator
The `*` operator allows you to access the data, held in the memory location **that the pointer points to**.
```c++
int x = 5;
int * ptr1 = &x;

cout << ptr1 << *ptr1 << x << endl;
x = 10;

cout << ptr1 << *ptr1 << x << endl;
*ptr1 = 16;

cout << ptr1 << *ptr1 << x << endl;

ptr1 = 42;  // wow.. this is really bad.
cout << ptr1 << *ptr1 << x << endl;
```
.callout[
Why is `ptr1 = 42` so awful?  Let's draw...
]

---
# Scope of heap variables
- When you create heap variables, you get an address in the **heap**.
- You are responsible for removing the variable from the heap when you are done!

```c++
int * ptr1 = new int(5); // not an array, just initializing the in to be 5.
int * ptr2 = new int(10);
int x = 20;

cout << x << *ptr1 << *ptr2 << endl;

*ptr1 = x;   // OK, copies x into the int ptr1 points to.
ptr2 = ptr1; // Seemingly fine... ptr2 now points to the same things as ptr1 
```

.callout[
How do we print out that int that has 10 in it now?  **We can't!**
]


---
# Scope of heap variables
- When you create heap variables, you get an address in the **heap**.
- You are responsible for removing the variable from the heap when you are done!

```c++
int * ptr1 = new int(5); // not an array, just initializing the in to be 5.
int * ptr2 = new int(10);
int x = 20;

cout << x << *ptr1 << *ptr2 << endl;

*ptr1 = x;   // OK, copies x into the int ptr1 points to.

delete ptr2; // De-allocates int that has 10, can be re-used.

ptr2 = ptr1; // ptr2 now points to the same things as ptr1 
```
.callout[
The `delete` operator frees up the space in memory when we don't want it any more.
]

---
# Dereferencing pitfalls
- When dereferencing (`*`), we are making the assumption that the pointer points to *something*.

```c++
int x = 5;
int * ptr1 = new int(10);
int * ptr2 = new int(20);
int * ptr3;

... 100s of lines later...

*ptr3 = 15;  // Crash... ptr3 doesn't point to anything!
```
.callout[
Could we have tested to see if ptr3 pointed to anything?
]

```c++
if ( ptr3 == "the abyss?") {

}
```

---
# Dereferencing pitfalls
- When dereferencing (`*`), we are making the assumption that the pointer points to *something*.

```c++
int x = 5;
int * ptr1 = new int(10);
int * ptr2 = new int(20);
int * ptr3 = nullptr;  // ALWAYS INITIALIZE if not yet assigned!

... 100s of lines later...

if ( ptr3 != nullptr ) {
    *ptr3 = 15;  
}
```
.callout[
Unitialized pointers have data in them... that look just like addresses - they are random integers.  Always initialize to nullptr so you can check against a known value. 
]


---
# Dereferencing pitfalls
- When dereferencing (`*`), we are making the assumption that the pointer points to *something*.

```c++
int x = 5;
int * ptr1 = new int(10);
int * ptr2 = new int(20);
int * ptr3 = new int(30);  

... 100s of lines later..

delete ptr3;  // Done using it!

... 100s of lines later...

if ( ptr3 != nullptr ) {
    *ptr3 = 15;  // Crash (?)
}
```
.callout[
You might crash, you might not... the pointer holds an address value that was reclaimed, and could be re-used already!  **Either way... not fun.**
]


---
# Dereferencing pitfalls
- When dereferencing (`*`), we are making the assumption that the pointer points to *something*.

```c++
int x = 5;
int * ptr1 = new int(10);
int * ptr2 = new int(20);
int * ptr3 = new int(30);  

... 100s of lines later..

delete ptr3;  // Done using it!
ptr3 = nullptr   // Always reset to nullptr so you can check later.!

... 100s of lines later...

if ( ptr3 != nullptr ) {
    *ptr3 = 15;  // Crash (?)
}
```

---
# Pointers to stack variables.
- Pointers to stack variables are fine, but make sure you don't return them!

```c++
int * return_pointer_to_sum(int a, int b) {
    int result = a + b;
    return &result; 
}
int main() {
    int * sum = return_pointer_to_sum(5, 6);
    cout << *sum << endl;  // Crash...
}
```
.callout[
Remember, the stack frame that the address points to is **destroyed** on function return!
]

---
# Pointers created in functions
```c++
int * return_pointer_to_sum(int a, int b) {
    int * result = new int(a + b); // Store result in heap
    return result;   // result is a pointer to wher you put the sum.
}
int main() {
    int * sum = return_pointer_to_sum(5, 6);
    cout << *sum << endl;  

    // You have a problem, unless you are exiting right away!
}
```
.callout[
Memory allocted on heap is **not** destroyed when you return from the function.
]

---
# Pointers created in functions
```c++
int * return_pointer_to_sum(int a, int b) {
    int * result = new int(a + b); // Store result in heap
    return result;   // result is a pointer to wher you put the sum.
}
int main() {
    int * sum = return_pointer_to_sum(5, 6);
    cout << *sum << endl;  

    delete sum;  
}
```
.callout[
Returning memory allocated by a function is dangerous, and should be avoided when you can - it's too easy to forget to delete!
]
---
# Pointer mistakes
I've shown you a bunch of common pitfalls of working with pointers and dynamic memory.  They fall into two classifications:
- **Memory leaks** - you forget to delete something, or lose all your pointer reference too it, and cannot delete it!
- **Dangling pointers** - you *forgot* you deleted something, or never even allocated space, and try to reference the pointer.

.callout[
Dynamic memory allocation is **hard**, and **pointer** are hard.  Unfortunately, we need them - but we will eventually learn some better ways of mitigating risk.
]
---
# Dynamic members
Sometimes our object may allocate data for themselves.
```c++
class IntBox {
    private:
        int * data;
    public: 
        IntBox(int v) {
            data =new int(v);
        }
};
```
.callout[
- When designing a class, you should **NEVER** make it the user's responsibility to cleanup your class's memory!
- Class instances **own** their data, users of the class should never need to know about how it is allocated.
-  **Never** ask a user of your class to delete one of your members - your member variables are `private`!
- **Never** ask a user of your class to call a function to clean up, they will forget.
]
---
# Destructors
The answer to the dynamic member variable problem is straightforward:
- A **destructor** is *automatically* called whenever a class instance goes out of scope.
- Your **destructor** should clean up memory allocations.

```c++
class IntBox {
    private:
        int * data;
    public: 
        IntBox(int v) {
            data =new int(v);
        }
        ~IntBox() {     // Called whenever instance goes out of scope
            delete data;
        }
};
```

---
# Objects on the heap
There is a difference between:
- objects on the stack, which contain heap member variables
- objects on the heap, which contain heap member variables.

```c++
void do_stuff() {
    IntBox boxPtr(5);
    // do stuff with the integer object
}
int main() {
    for ( int i = 0; i < 10; i++)  do_stuff();
}
```
.callout[
This is safe, the boxPtr object is declared on the stack, and goes out of scope each time `do_stuff` returns, which invokes the constructor.
]

---
# Objects on the heap
There is a difference between:
- objects on the stack, which contain heap member variables
- objects on the heap, which contain heap member variables.

```c++
void do_stuff() {
    IntBox * boxPtr = new IntBox(5);
    // do stuf with the integer object
}
int main() {
    for ( int i = 0; i < 10; i++)  do_stuff();
}
```
.callout[
This is a **memory leak**, the `IntBox` is created on the heap, it never goes out of scope.  It's destructor is never called.
]

---
# Objects on the heap
There is a difference between:
- objects on the stack, which contain heap member variables
- objects on the heap, which contain heap member variables.

```c++
void do_stuff() {
    IntBox * boxPtr = new IntBox(5);
    // do stuf with the integer object
    delete boxPtr;
}
int main() {
    for ( int i = 0; i < 10; i++)  do_stuff();
}
```
.callout[
`delete` operator call the destructor, so this is safe.
]

---
# Implementing a basic `vector` 
A `vector` can grow to accomodate more data.  Now we know how...

.callout[
Let's change our ArrayList so:
1. It accepts any data type
2. It automatically grows by a factor of two when out of room.
]

To "grow", we need to do the following:
1. The `data` array member should be heap allocated (perhaps initial size of 100)
2. If the count gets too big, we:
  1. Create a new array (temporary pointer) twice as big as `data`
  2. Copy contents of `data` into `tmp` array.
  3. Delete `data` - deleting the old array.
  4. Set `data` pointer to point to the `tmp` array.




