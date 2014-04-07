cmake_minimum_required(VERSION 2.8)

# setup

set(CMAKE_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake-modules/)
set(${CMAKE_CURRENT_BINARY_DIR} "${CMAKE_CURRENT_BINARY_DIR}/bin")

include(${CMAKE_MODULES_DIR}/FindRagel.cmake)
include(${CMAKE_MODULES_DIR}/lemon.cmake)

get_filename_component(DIR_ABOVE ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
include_directories(${DIR_ABOVE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wall  -std=c++11 ${CMAKE_CXX_FLAGS}")

# configure the library

# generate the lexer
ragel_gen(rl_parser)
set_source_files_properties(
    SOURCE "rl_parser.cc"
    PROPERTIES
        GENERATED TRUE
        OBJECT_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/asm_grammar.rl
)

# generate the parser
LEMON(parser parser LEMON_FILES)

add_library(parser
    rl_parser.cc
    ${DIR_ABOVE}/opcodes/opcodes.cpp
)

add_custom_target(lemon_files DEPENDS ${LEMON_FILES})
add_dependencies(parser
    lemon_files
    ragelrl_parser
)
