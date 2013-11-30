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
#define SET_STR const std::unordered_set<std::string>

namespace galaxy { namespace jupiter {
    class TokenError : std::exception {
    public:
        TokenError(std::string msg) : msg(msg) {};
        ~TokenError() {};
        std::string msg;

        virtual const char* what() const noexcept {
            return msg.c_str();
        }
    };

    std::string char_repr(std::string);

    class tokenizer {
    private:
        std::string tokens = "";
        int _length;
        int _upto;

        SET_STR WHITESPACE = {"\t", " ", "\r"};
        SET_STR PUNCTUATION = {",", ".", "\n", ";", "\"", "[", "]"};
        SET_STR BINARY_B = {"b", "B"};
        SET_STR BINARY_CHARS = {"0", "1"};
        SET_STR HEX_X = {"x", "X"};

        std::string peek();
        char peek_char();
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

        void load_token_string(std::string tokens){
            std::cout << "Lexer initialized with: " << std::endl;
            std::cout << "##########" << std::endl;
            std::cout << tokens << "##########" << std::endl << std::endl;

            _length = tokens.length();
            _upto = 0;
        }

        tokenizer(std::string tokens) {
            load_token_string(tokens);
        }

        template<typename Iter>
        tokenizer(Iter begin, Iter end) {
            load_token_string(std::string(begin, end));
        }

    };

    std::string get_file_contents(std::string path);
}}

#endif
