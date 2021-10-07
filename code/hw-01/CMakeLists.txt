cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)

# This names our project
project (hw1)


enable_testing()
add_test( Tests hw1-test)


# add the dependencies - the other source code files in your program
include_directories(./includes)
include_directories(../utils)

add_library(generate includes/generate.cpp)

# This defines the name of our executable, and the file that contains main.
add_executable(hw1-ui main.cpp)
target_link_libraries(hw1-ui generate)

# Add another executable for testing
add_executable(hw1-test test.cpp)
target_link_libraries(hw1-test generate)

