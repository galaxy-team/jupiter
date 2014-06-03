enable_testing()

include_directories(${CMAKE_BINARY_DIR}/src/lib/)

add_executable(test_jupiter
    test.cpp
    utils.cpp

    tests/parsing.cpp
    tests/assembling.cpp
)

target_link_libraries(test_jupiter libjupiter)

add_test(test_jupiter bin/test_jupiter)
