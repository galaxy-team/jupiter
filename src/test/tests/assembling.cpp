#include "../catch.hpp"
#include "../utils.hpp"

#include "rl_parser/rl_parser.hpp"
// for the different token types
#include "rl_parser/parser.h"
#include "opcodes/opcodes.hpp"

// TEST_CASE("Test basic parsing", "[parsing,basic_opcode]") {
//     REQUIRE_OPS_TO_ASM(
//         "ADD A, A",
//         O(basic)(
//             "ADD",
//             P(REGISTER, "A"),
//             P(REGISTER, "A")
//         )
//     );
// }

// TEST_CASE("Test basic reference parsing", "[parsing,basic_opcode]") {
//     REQUIRE_OPS_TO_ASM(
//         "ADD A, [A]",
//         O(basic)(
//             "ADD",
//             P(REGISTER, "A"),
//             P(REGISTER, "[A]")
//         )
//     );
// }

// TEST_CASE("Test special opcode parsing", "[parsing,special_opcode]") {
//     REQUIRE_OPS_TO_ASM(
//         "INT 0",
//         O(special)(
//             "INT",
//             P(DECIMAL, "0")
//         )
//     );
// }

TEST_CASE("Test dat opcode assembling", "[assembling,dat_directive") {
    REQUIRE_OPS_TO_ASM(
        {O(dat)("w")},
        {0x77}
    );
}

TEST_CASE("Test fill directive assembling", "[assembling,fill_directive]") {
    REQUIRE_OPS_TO_ASM(
        {O(fill)(0xCAFE, 0x5)},
        {0xCAFE, 0xCAFE, 0xCAFE, 0xCAFE, 0xCAFE}
    );
}

TEST_CASE("Test orig directive assembling", "[assembling,orig_directive]") {
    REQUIRE_OPS_TO_ASM(
        {O(orig)(0x05), O(dat)("w")},
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x77}
    );
}
