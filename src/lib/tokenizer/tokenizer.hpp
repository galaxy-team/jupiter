#include <string>
#include <unordered_set>
#include <vector>
#include "token.hpp"

#ifndef _TOKENISER_HPP
#define _TOKENISER_HPP

// #define UNEXP_END_STRING "Unexpected end of string while parsing Lua string."
// #define UNEXP_END_TABLE "Unexpected end of table while parsing Lua string."
#define MFNUMBER_MINUS "Malformed number (no digits after initial minus)."
#define MFNUMBER_DEC_POINT "Malformed number (no digits after decimal point)."
#define MFNUMBER_SCI "Malformed number (bad scientific format)."
#define IN_SET(str,set) (set.count(str.c_str()) > 0)
#define PEEK_IS(set) (IN_SET(peek(), set))
#define SET_STR std::unordered_set<std::string>

namespace galaxy {
    namespace jupiter {
        class tokenizer {
        private:
            std::string tokens = "";
            int _length;
            int _upto;

            SET_STR NUMBERS = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
            SET_STR ALPHANUM = {
                "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
                "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"
            };
            SET_STR WHITESPACE = {"\t", " "};
            SET_STR PUNCTUATION = {",", ".", "\n", ";"};
            SET_STR BINARY_B = {"b", "B"};
            SET_STR BINARY_CHARS = {"0", "1"};
            SET_STR HEX_X = {"x", "X"};
            SET_STR HEX_CHARS = {"A","B","C","D","E","F","a","b","c","d","e","f"};

            std::string peek();
            bool end();
            bool is_digit();
            void step();
            void white();
            std::string word();
            std::string punctuation();
            std::string digit();
            std::string hex();
            std::string binary();
            std::string next_digit(std::string err);
            std::string number();
            galaxy::jupiter::Token* value();

        public:
            std::vector<galaxy::jupiter::Token*> lex();

            tokenizer(std::string tokens) : tokens(tokens) {
                std::cout << "Lexer initialized with: " << std::endl;
                std::cout << "##########" << std::endl;
                std::cout << tokens << "##########" << std::endl << std::endl;

                _length = tokens.length();
                _upto = 0;
            }

            template<typename Iter>
            tokenizer(Iter begin, Iter end) {
                tokens = std::string(begin, end);

                std::cout << "Lexer initialized with: " << std::endl;
                std::cout << "##########" << std::endl;
                std::cout << tokens << "##########" << std::endl << std::endl;

                _length = tokens.length();
                _upto = 0;
            }
        };

        std::string get_file_contents(std::string path);
    }
}

#endif
