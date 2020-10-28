cmake_minimum_required(VERSION 3.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
project(OptimalHammingCode)

add_subdirectory(qc)

add_subdirectory(matrix)

option(OHC_TESTS "Build tests" OFF)
if(OHC_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
