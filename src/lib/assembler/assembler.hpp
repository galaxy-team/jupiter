#include <vector>
#include <unordered_map>
#include <string>

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
                    return msg.c_str();
                }
            };

            std::unordered_map<std::string, std::uint16_t> find_symbols(
                OPCODE_VECTOR opcodes
            );

            galaxy::asteroid pass_two(
                OPCODE_VECTOR opcodes,
                std::unordered_map<std::string,
                std::uint16_t> symbol_map
            );

            extern const std::unordered_map<std::string, std::uint16_t> basic_opcodes;
        }
    }
}
