cmake_minimum_required(VERSION 2.8.5)
project(jupiter)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-pedantic-errors -Wall -Wextra -O0 -ggdb -Wfatal-errors -Wwrite-strings -ftrapv -fno-merge-constants -fno-nonansi-builtins -fno-gnu-keywords -fstrict-aliasing ${CMAKE_CXX_FLAGS}")

set(THIRD-PARTY ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/asteroid)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/asteroid)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules/FindGlog.cmake)
if (NOT GLOG_FOUND)
    message(FATAL_ERROR "GLog not found")
endif()

set(OPTIONPARSER_DIR ${THIRD-PARTY}/optparse/)
include_directories(${OPTIONPARSER_DIR})
if (TARGET optionparser)
    message(STATUS "OptionParser already built as part of another part of Galaxy")
else()
    # setup OptionParser
    add_library(optionparser
        ${OPTIONPARSER_DIR}/OptionParser.cpp
    )
endif()

# setup libjupiter
set(JUPITER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

include_directories(${JUPITER_SOURCE_DIR})
add_library(libjupiter
    ${JUPITER_SOURCE_DIR}/libjupiter.cpp
    ${JUPITER_SOURCE_DIR}/tokenizer/token.cpp
    ${JUPITER_SOURCE_DIR}/assembler/assembler.cpp
    ${JUPITER_SOURCE_DIR}/opcodes/opcodes.cpp
    ${JUPITER_SOURCE_DIR}/utils.cpp

    # the parser
    src/lib/rl_parser/rl_parser.cc
)
# we dont want liblibjupiter :P
set_target_properties(libjupiter PROPERTIES PREFIX "")
target_link_libraries(libjupiter ${GLOG_LIBRARIES})

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules/FindRagel.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules/lemon.cmake)

# build the lexer
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/src/lib/rl_parser)
include_directories(${JUPITER_SOURCE_DIR}/rl_parser)
ragel_gen(src/lib/rl_parser/rl_parser)
set_source_files_properties(
    SOURCE ${JUPITER_SOURCE_DIR}/rl_parser/rl_parser.cc
    PROPERTIES
        GENERATED TRUE
        OBJECT_DEPENDS ${JUPITER_SOURCE_DIR}/rl_parser/asm_grammar.rl
)
# lexer done

# generate the parser
LEMON(
    src/lib/rl_parser/parser
    src/lib/rl_parser/parser
    LEMON_FILES
)
add_custom_target(lemon_files DEPENDS ${LEMON_FILES})
# parser done

# tell cmake what libjupiter needs
add_dependencies(libjupiter
    lemon_files
    ragelrl_parser
)

add_executable(jupiter
    src/main.cpp
)

target_link_libraries(jupiter
    libjupiter
    optionparser
)


# tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/test)
