cmake_minimum_required(VERSION 3.16)
project(matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(matrix
        include/matrix.h
        src/main.cpp
        src/matrix.cpp)
