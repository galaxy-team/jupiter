#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

#include <libasteroid.hpp>

namespace galaxy {
    namespace jupiter {
        namespace assembler {
            class UnknownOpcode : std::exception {
            public:
                virtual ~UnknownOpcode() {};
                UnknownOpcode(std::string msg) : msg(msg) {};
                std::string msg;

                virtual const char* what() const noexcept {
                    std::stringstream ss;
                    ss << "No such opcode: " << msg;
                    return ss.str().c_str();
                }
            };

            std::unordered_map<std::string, std::uint16_t> find_symbols(
                OPCODE_VECTOR opcodes
            );

            OPCODE_VECTOR pass_two(
                OPCODE_VECTOR opcodes,
                SYMBOL_MAP symbol_map
            );

            extern const std::unordered_map<std::string, std::uint16_t> basic_opcodes;
            extern const std::unordered_map<std::string, std::uint16_t> special_opcodes;
            extern const std::unordered_map<std::string, std::uint16_t> values;
        }
    }
}
