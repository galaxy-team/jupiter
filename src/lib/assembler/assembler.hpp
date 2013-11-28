#include <vector>
#include <unordered_map>
#include <string>

#include <libasteroid.hpp>

namespace galaxy {
    namespace jupiter {
        namespace assembler {
            std::unordered_map<std::string, std::uint16_t> find_symbols(
                OPCODE_VECTOR opcodes
            );

            galaxy::asteroid pass_two(
                OPCODE_VECTOR opcodes,
                std::unordered_map<std::string,
                std::uint16_t> symbol_map
            );
        }
    }
}
