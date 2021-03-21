cmake_minimum_required(VERSION 3.17)
project(Laba2)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(/usr/src/gtest [binary_dir])
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(Laba2 Tests.cpp)
target_link_libraries(Laba2 gtest gtest_main)
