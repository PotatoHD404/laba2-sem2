cmake_minimum_required(VERSION 3.16)
project(Laba2)

add_compile_options(--coverage)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tests)

add_subdirectory(tempNew)

add_executable(Laba2 main.cpp)

