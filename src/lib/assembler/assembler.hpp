#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include <libasteroid.hpp>
#include <opcodes/opcodes.hpp>
#include <tokenizer/tokenizer.hpp>
#include <parser/parser.hpp>

namespace galaxy {
    namespace jupiter {
        namespace assembler {
            std::unordered_map<std::string, std::uint16_t> find_symbols(std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes);

            galaxy::asteroid pass_two(std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes, std::unordered_map<std::string, std::uint16_t> symbol_map);
        }
    }
}
