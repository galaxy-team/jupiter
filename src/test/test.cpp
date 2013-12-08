#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "libjupiter.hpp"

TEST_CASE("Initialization", "") {
    std::string input = "ADD A,1\n";

    auto objfile = galaxy::jupiter::assemble(input.begin(), input.end());
}

TEST_CASE("Test basic opcodes", "[basic_opcode]") {
    std::string input = "ADD A,1\nSUB A,1\n";

    auto objfile = galaxy::jupiter::assemble(input.begin(), input.end());

    REQUIRE(objfile.object_code.at(0) == 0x8801);
    REQUIRE(objfile.object_code.at(1) == 0x8803);
}
