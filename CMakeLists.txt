cmake_minimum_required(VERSION 3.3)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(Thesis)

enable_testing()

add_subdirectory(veamy)
add_subdirectory(x-poly)
add_subdirectory(test)


