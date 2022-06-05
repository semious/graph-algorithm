cmake_minimum_required(VERSION 3.22)
project(graph_algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(./)
include_directories(src/cpp)
include_directories(test/cpp)
include_directories(test/cpp/catch2)

add_executable(graph_algorithm
        src/cpp/wasm.hpp
        src/cpp/wasm.cpp
        src/cpp/graph.hpp
        src/cpp/kernel/force.cpp
        src/cpp/kernel/force.hpp
        )

#add_executable(graph_algorithm_test
#        test/cpp/test_util.h
#        test/cpp/force_test.cpp
#        )
