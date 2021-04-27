cmake_minimum_required(VERSION 3.16)
project(Laba2)

set(CMAKE_CXX_FLAGS "-Wall -fprofile-arcs -ftest-coverage -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")

enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tests)

add_executable(Laba2 main.cpp)


