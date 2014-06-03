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

void REQUIRE_ASM(std::string input_string, std::vector<std::bitset<16>> vector_required) {
    auto objfile = bitset_assemble(input_string.begin(), input_string.end());
    REQUIRE(objfile == vector_required);
}
