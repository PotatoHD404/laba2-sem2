cmake_minimum_required(VERSION 3.16)
project(Laba2)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
endif()

#target_link_libraries(gcov)

set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage")

add_compile_options(--coverage)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Tests)

add_subdirectory(tempNew)

add_executable(Laba2 main.cpp)

