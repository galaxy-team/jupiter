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
            galaxy::jupiter::opcodes::LabelOpcode* handle_label(HANDLER_SIGNATURE);
        }
    }
}

#endif
