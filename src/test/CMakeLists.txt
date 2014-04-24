enable_testing()

add_executable(test_jupiter test.cpp)
target_link_libraries(test_jupiter libjupiter)

add_test(test_jupiter bin/test_jupiter)
