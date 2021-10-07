# Homework 1 - Queue practice

Write a main program that accepts an unsigned from the user.  Implement (and call) a function that accepts an unsigned `n`, and returns **vector&lt;string&gt;**, of all the binary representations of the numbers 1 through `n`.

**For example**:
- `generate(1)` would return `["1"]`
- `generate(3)` would return `["1","10","11"]`
- check out test.cpp for more examples

## Requirements
Your function (`generate`) must use a queue to construct the binary representations of numbers

The general algorithm should be as follows:
- **Setup**: Place `"1"` in the queue and initialize a counter
- **Step 1**: Add `"0"` to the item at the front of the queue and push that onto the queue
- **Step 2**: Add `"1"` to the item at the front of the queue and push that onto the queue
- **Step 3**: Accumulate the item at the front of the queue in your vector
- **Step 4**: **Pop** the front of the queue off - don't forget this step :)
- **Step 5**: Increment counter - loop until counter reaches `n`

**Failure to use a queue as explained above will result in zero credit -** the purpose of this exercise is to gain experience with the STL queue.

## Submission Requirements
I have provided you a directory structure with code files ready for use.  In `main.cpp` you should write your program that accepts two strings from the user, and calls `generate`.  In `includes/generate.h` and `includes/generate.cpp` you should add your implementation of the generate function.  `test.cpp` contains the set of test cases that I will use to grade your work.

**Please zip up the entire directory structure** (remove the `/build` directory, so you aren't including executables) and submit to Canvas by the submission deadline.

**You do not need to include `utils/catch.hpp` in your zip file - just the folder with the homework code.  I will provide the `catch.hpp` library.