cmake_minimum_required(VERSION 3.22)
project(graph_algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/cpp/fruchterman)

add_executable(graph_algorithm
        src/cpp/fruchterman/fruchterman-simd.cpp
        src/cpp/fruchterman/fruchterman.cpp
        src/cpp/fruchterman/fruchterman.h)
