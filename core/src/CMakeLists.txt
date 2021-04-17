cmake_minimum_required(VERSION 3.16)
project(Laba2)

#target_link_libraries(gcov)
set(CMAKE_CXX_FLAGS "-g -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
SET(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")

#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})
#
#find_package(codecov)

enable_testing()

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tests)

#add_subdirectory(tempNew)

add_executable(Laba2 main.cpp)


