cmake_minimum_required(VERSION 3.16)
project(Laba2)

#target_link_libraries(gcov)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})

find_package(codecov)

#set(CMAKE_CXX_FLAGS "-g -Wall")
#
#add_compile_options(--coverage)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tests)

add_subdirectory(tempNew)

add_executable(Laba2 main.cpp)
add_coverage(Laba2)

