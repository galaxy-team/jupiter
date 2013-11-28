// standard library
#include <vector>

// application specific
#include "opcodes/opcodes.hpp"
#include "tokenizer/token.hpp"

#ifndef _PARSER_HPP
#define _PARSER_HPP

#define TOKEN_VECTOR std::vector<galaxy::jupiter::Token*>
#define HANDLER_SIGNATURE galaxy::jupiter::Token* token, TOKEN_VECTOR &tokens

namespace galaxy {
    namespace jupiter {
        namespace parser {
            struct InvalidInstruction : ParserError {
                InvalidInstruction(std::string msg, std::string inst) : msg(msg), inst(inst) {};
                InvalidInstruction(std::string msg, Token* token) : msg(msg) {
                    msg = token->repr();
                };
                std::string msg;
                std::string inst;
                const char* what(){
                    std::stringstream ss;
                    ss << msg << inst;
                    return ss.str().c_str();
                }
            };

            class Parser {
            private:
                std::vector<galaxy::jupiter::Token*> tokens;

            public:
                Parser(std::vector<galaxy::jupiter::Token*> tokens) : tokens(tokens) {};

                template<typename Iter>
                Parser(Iter begin, Iter end) {
                    tokens = std::vector<galaxy::jupiter::Token*>(begin, end);
                };

                std::vector<galaxy::jupiter::opcodes::Opcode*> parse();
            };


            // we find a problem, we fix it -.-
            template<typename T>
            T pop(std::vector<T>& v){
                T item = v.front();
                v.erase(v.begin());
                return item;
            }

            galaxy::jupiter::opcodes::OrigOpcode* handle_orig(HANDLER_SIGNATURE);
            galaxy::jupiter::opcodes::InstructionOpcode* handle_inst(HANDLER_SIGNATURE);
            void handle_comments(HANDLER_SIGNATURE);
            galaxy::jupiter::opcodes::DATOpcode* handle_dat(HANDLER_SIGNATURE);
            galaxy::jupiter::opcodes::LabelOpcode* handle_label(HANDLER_SIGNATURE);
        }
    }
}

#endif
