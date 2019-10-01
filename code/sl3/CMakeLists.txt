cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)

# This names our project
project (deque)


enable_testing()
add_test( Tests testing)


# add the dependencies - the other source code files in your program
include_directories(./includes)
include_directories(../utils)

add_library(deque includes/deque.cpp)

# This defines the name of our executable, and the file that contains main.
add_executable(deque-ui main.cpp)
target_link_libraries(deque-ui deque)

# Add another executable for testing
add_executable(testing test.cpp)
target_link_libraries(testing deque)

