#ifndef TEST_UTILS_CPP
#define TEST_UTILS_CPP

#include <bitset>
#include <vector>
#include "opcodes/opcodes.hpp"
#include "assembler/assembler.hpp"
#include "libasteroid.hpp"

std::vector<std::bitset<16>> asteroid_to_bitsets(galaxy::asteroid in_aster);
std::vector<std::bitset<16>> bitset_assemble(
    std::string::const_iterator begin,
    std::string::const_iterator end
);

void REQUIRE_ASM(std::string input_string, std::vector<std::bitset<16>> vector_required);
void REQUIRE_OPS_TO_ASM(opcode_vector opcodes, std::vector<std::bitset<16>> vector_required);

#define T(token_type, contents) \
    new galaxy::jupiter::token(token_type, contents)

#define P(token_type, contents) \
    new galaxy::jupiter::opcodes::part(\
        T(token_type, contents)  \
    )

#define O(type) new galaxy::jupiter::opcodes::type##_opcode

#define REQUIRE_OPCODES(a, b) REQUIRE(a->repr() == a->repr())

#define REQUIRE_OPCODE_SINGLE(input, correct) \
    REQUIRE_OPCODES(galaxy::jupiter::parser::parse(input)[0], correct)

#endif
