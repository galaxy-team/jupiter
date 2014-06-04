#include "../catch.hpp"
#include "../utils.hpp"

#include "rl_parser/rl_parser.hpp"
#include "rl_parser/parser.h"

TEST_CASE("Test basic parsing", "[parsing,basic_opcode]") {
    REQUIRE_OPCODE_SINGLE(
        "ADD A, A",
        O(basic)(
            "ADD",
            P(REGISTER, "A"),
            P(REGISTER, "A")
        )
    );
}

TEST_CASE("Test basic reference parsing", "[parsing,basic_opcode]") {
    REQUIRE_OPCODE_SINGLE(
        "ADD A, [A]",
        O(basic)(
            "ADD",
            P(REGISTER, "A"),
            P(REGISTER, "[A]")
        )
    );
}

TEST_CASE("Test special opcode parsing", "[parsing,special_opcode]") {
    REQUIRE_OPCODE_SINGLE(
        "INT 0",
        O(special)("INT", P(DECIMAL, "0"))
    );
}

TEST_CASE("Test fill directive parsing", "[parsing,fill_directive]") {
    REQUIRE_OPCODE_SINGLE(
        ".FILL 0xCAFEBABE 0x90",
        O(fill)(
            T(HEXADECIMAL, "0xCAFEBABE"),
            T(HEXADECIMAL, "0x90")
        )
    );
}

TEST_CASE("Test orig directive parsing", "[parsing,orig_directive]") {
    REQUIRE_OPCODE_SINGLE(
        ".ORIG 0x800",
        O(orig)(
            T(HEXADECIMAL, "0x800")
        )
    );
}

TEST_CASE("Test syntax error", "[parsing]") {
    REQUIRE_THROWS_AS(
        galaxy::jupiter::parser::parse("."),
        galaxy::jupiter::parser::syntax_error
    );
}
