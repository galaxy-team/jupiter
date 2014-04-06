cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake-modules/)
set(${CMAKE_CURRENT_BINARY_DIR} "${CMAKE_CURRENT_BINARY_DIR}/bin")

include(${CMAKE_MODULES_DIR}/FindRagel.cmake)
include(${CMAKE_MODULES_DIR}/lemon.cmake)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "-g -std=c++11 ${CMAKE_CXX_FLAGS}")

# generate the required files
ragel_gen(rl_parser)
set_source_files_properties("rl_parser.cc" PROPERTIES GENERATED TRUE)
LEMON(parser parser LEMON_FILES)

add_executable(parser
    rl_parser.cc
)

add_custom_target(lemon_files DEPENDS ${LEMON_FILES})
add_dependencies(parser
    lemon_files
    ragelrl_parser
)
