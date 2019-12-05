cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)

project (sorting)

enable_testing()
add_test( Tests testing)

include_directories(./includes)
include_directories(../utils)

add_library(sorting includes/sorting.cpp)


add_executable(sorting-ui main.cpp)
target_link_libraries(sorting-ui sorting)


# Add another executable for testing
add_executable(testing testing.cpp)
target_link_libraries(testing sorting)

