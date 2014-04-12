#ifndef _ASSEMBLER_HPP
#define _ASSEMBLER_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

#include <libasteroid.hpp>

namespace galaxy {
    namespace jupiter {
        namespace assembler {
            class UnknownOpcode : public std::exception {
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

            class UnknownLabel : public std::exception {
            public:
                virtual ~UnknownLabel() {};
                UnknownLabel(std::string msg) : msg(msg) {};
                std::string msg;

                virtual const char* what() const noexcept {
                    std::stringstream ss;
                    ss << "No such label: " << msg;
                    return ss.str().c_str();
                }
            };

            symbol_map find_symbols(
                opcode_vector opcodes
            );

            opcode_vector pass_two(
                opcode_vector opcodes,
                symbol_map symbol_map
            );

            galaxy::asteroid resolve_to_bytecode(
                opcode_vector opcodes,
                symbol_map symbol_map
            );

            extern const std::unordered_map<std::string, std::uint16_t> basic_opcodes;
            extern const std::unordered_map<std::string, std::uint16_t> special_opcodes;
            extern const std::unordered_map<std::string, std::uint16_t> values;
        }
    }
}

#endif
