#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "utils.hpp"

#include "libjupiter.hpp"

TEST_CASE("Initialization", "") {
    std::string input = "ADD A,1\n";

    auto objfile = galaxy::jupiter::assemble(input.begin(), input.end());
}

TEST_CASE("Test basic opcodes", "[basic_opcode]") {
    std::string input = "ADD A,1\nSUB A,1\n";

    REQUIRE_ASM(input, {
        0x8801,
        0x8803
    });
}
