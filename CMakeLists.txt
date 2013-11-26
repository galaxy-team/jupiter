cmake_minimum_required(VERSION 2.8.5)
project(jupiter)

set(CMAKE_BUILD_TYPE DEBUG)
#set(VERBOSE, True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS "--std=c++11 ${CMAKE_CXX_FLAGS}")
set(THIRD-PARTY ${CMAKE_CURRENT_SOURCE_DIR}/third-party)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/asteroid)

# setup OptionParser
set(OPTIONPARSER_DIR ${THIRD-PARTY}/optparse/)
add_library(optionparser
    ${OPTIONPARSER_DIR}/OptionParser.cpp
)
include_directories(${OPTIONPARSER_DIR})

# setup libjupiter
set(JUPITER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/lib)
include_directories(${JUPITER_SOURCE_DIR})
add_library(libjupiter
    ${JUPITER_SOURCE_DIR}/libjupiter.cpp
    ${JUPITER_SOURCE_DIR}/tokenizer/tokenizer.cpp
    ${JUPITER_SOURCE_DIR}/tokenizer/token.cpp
    ${JUPITER_SOURCE_DIR}/parser/parser.cpp
    ${JUPITER_SOURCE_DIR}/assembler/assembler.cpp
    ${JUPITER_SOURCE_DIR}/opcodes/opcodes.cpp
)
set_target_properties(libjupiter PROPERTIES PREFIX "")

add_executable(jupiter
    src/main.cpp
)

target_link_libraries(jupiter
    libjupiter
    optionparser
)
