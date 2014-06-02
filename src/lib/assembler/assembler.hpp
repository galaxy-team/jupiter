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
            class assembler_exception : public std::runtime_error {
            public:
                virtual ~assembler_exception() {};
                assembler_exception() : std::runtime_error("") {};
                assembler_exception(std::string msg) : assembler_exception(msg) {};
                std::string msg;

                virtual const char* what() const noexcept {
                    std::stringstream ss;
                    ss << "No such opcode: " << msg;
                    return ss.str().c_str();
                }
            };

            class unknown_opcode : public assembler_exception {
            public:
                virtual ~unknown_opcode() {};
                unknown_opcode(std::string msg) : assembler_exception(msg) {};

                virtual const char* what() const noexcept {
                    std::stringstream ss;
                    ss << "No such opcode: " << msg;
                    return ss.str().c_str();
                }
            };

            class unknown_label : public assembler_exception {
            public:
                virtual ~unknown_label() {};
                unknown_label(std::string msg) : assembler_exception(msg) {};
                std::string msg;

                virtual const char* what() const noexcept {
                    std::stringstream ss;
                    ss << "No such label: " << msg;
                    return ss.str().c_str();
                }
            };

            class bad_origin : public assembler_exception {
            public:
                bad_origin(std::uint16_t address) : address(address) {};
                std::uint16_t address;

                virtual const char* what() const noexcept {
                    std::stringstream ss;
                    ss << "Program has already advanced past address 0x";
                    ss << std::hex << address;
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
