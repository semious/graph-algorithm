cmake_minimum_required(VERSION 3.22)
project(graph_algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(./)
include_directories(src/cpp)
include_directories(test/cpp)

add_executable(graph_algorithm
        src/cpp/fruchterman_simd.cpp
        src/cpp/fruchterman_simd.h
        src/cpp/fruchterman.cpp
        src/cpp/fruchterman.h
        src/cpp/graph.h)

add_executable(graph_algorithm_test
        test/cpp/test_util.h
        test/cpp/fruchterman_test.cpp
        test/cpp/fruchterman_simd_test.cpp
        )
