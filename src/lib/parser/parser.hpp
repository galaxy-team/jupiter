// standard library
#include <vector>

// application specific
#include "opcodes/opcodes.hpp"
#include "tokenizer/token.hpp"

#ifndef _PARSER_HPP
#define _PARSER_HPP

namespace galaxy {
    namespace jupiter {
        namespace parser {
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
            galaxy::jupiter::opcodes::DATOpcode* handle_dat(HANDLER_SIGNATURE);
            galaxy::jupiter::opcodes::LabelOpcode* handle_label(HANDLER_SIGNATURE);
        }
    }
}

#endif
