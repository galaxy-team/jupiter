#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <sstream>
#include <bitset>
#include "libjupiter.hpp"

std::vector<std::bitset<16>> bitset_assemble(
    std::string::const_iterator begin,
    std::string::const_iterator end
)
{
    auto objfile = galaxy::jupiter::assemble(begin, end);
    std::vector<std::bitset<16>> bitset_repres;
    for (auto it: objfile.object_code) {
        bitset_repres.push_back(it);
    }
    return bitset_repres;
}

void REQUIRE_ASM(std::string input_string, std::vector<std::bitset<16>> vector_required) {
    auto objfile = bitset_assemble(input_string.begin(), input_string.end());
    REQUIRE(objfile == vector_required);
}

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

#include "rl_parser/rl_parser.hpp"
#include "rl_parser/parser.h"

#define T(token_type, contents) \
    new galaxy::jupiter::Token(token_type, contents)

#define P(token_type, contents) \
    new galaxy::jupiter::opcodes::Part(\
        T(token_type, contents)  \
    )

#define REQUIRE_OPCODES(a, b) REQUIRE(a->repr() == a->repr())

TEST_CASE("Test basic parsing", "[parsing]") {
    std::string input = "ADD A, A";

    auto opcodes = galaxy::jupiter::parser::parse(input);

    opcode_vector correct = {
        new galaxy::jupiter::opcodes::BasicOpcode(
            "ADD",
            P(REGISTER, "A"),
            P(REGISTER, "A")
        )
    };

    REQUIRE_OPCODES(opcodes[0], correct[0]);
}
