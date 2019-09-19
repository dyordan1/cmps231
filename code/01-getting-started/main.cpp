#include <iostream>

/* Important - notice that hello.h is actually 
   in an other directory.  CMake handles the 
   resolution.  
   
   If you are getting a warning/error (red underline)
   in your source code editor (VSCode), you haven't
   configured your CMakeLists.txt file correctly, or
   you haven't installed the VSCode CMake plugin!
*/
#include "hello.h"

/* This is a simple hello-world program
   designed to ensure that you have set up
   your build environment correctly.
*/
int main()
{
    int x;
    std::cout << "Hello directly from main..." << std::endl;
    say_hello();
    std::cin >> x;
    std::cout << "2 + 3 is " << add(2, 3) << std::endl;
}