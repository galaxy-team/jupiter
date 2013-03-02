cmake_minimum_required(VERSION 2.8.5)
project(jupiter)

set(VERBOSE, True)

set(CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/asteroid)

add_executable(jupiter
    src/main.cpp
    src/lib/libjupiter.cpp
)
