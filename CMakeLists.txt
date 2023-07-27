cmake_minimum_required(VERSION 3.26)
project(therappeye)

set(CMAKE_CXX_STANDARD 17)

include_directories(./src/)
include_directories(SYSTEM /usr/local/include/)

add_executable(therappeye
        src/main.cpp
        src/main.cu
        src/presentation.cpp
        src/presentation.hpp)
