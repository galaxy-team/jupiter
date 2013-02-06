cmake_minimum_required(VERSION 2.8.5)
project(jupiter)

#set(VERBOSE, True)

set(CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")

add_executable(jupiter
    src/main.cpp
    src/lib/libjupiter.hpp
    src/lib/libjupiter.cpp
)
