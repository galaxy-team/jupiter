#include "catch.hpp"

#include "utils.hpp"
#include "libjupiter.hpp"


std::vector<std::bitset<16>> bitset_assemble(
    std::string::const_iterator begin,
    std::string::const_iterator end
)
{
    return asteroid_to_bitsets(
        galaxy::jupiter::assemble(begin, end)
    );
}

std::vector<std::bitset<16>> asteroid_to_bitsets(galaxy::asteroid in_aster) {
    std::vector<std::bitset<16>> bitset_repres;
    for (auto it: in_aster.object_code) {
        bitset_repres.push_back(it);
    }
    return bitset_repres;
}

void REQUIRE_OPS_TO_ASM(opcode_vector opcodes, std::vector<std::bitset<16>> vector_required) {
    auto symbol_map = galaxy::jupiter::assembler::find_symbols(opcodes);
    opcodes = galaxy::jupiter::assembler::pass_two(opcodes, symbol_map);
    auto aster = galaxy::jupiter::assembler::resolve_to_bytecode(opcodes, symbol_map);
    REQUIRE(asteroid_to_bitsets(aster) == vector_required);
}


void REQUIRE_ASM(std::string input_string, std::vector<std::bitset<16>> vector_required) {
    auto objfile = bitset_assemble(input_string.begin(), input_string.end());
    REQUIRE(objfile == vector_required);
}
