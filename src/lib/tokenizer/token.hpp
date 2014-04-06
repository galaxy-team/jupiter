#ifndef _TOKEN_HPP
#define _TOKEN_HPP

#include <vector>

namespace galaxy { namespace jupiter {

class Token {
public:
    int token_type;
    std::uint16_t line_no;
    std::string contents;
    std::string token_name;

    Token(int token_type, std::string contents) :
        token_type(token_type),
        line_no(0),
        contents(contents),
        token_name("") {};

    Token(int token_type, std::string contents, std::string token_name) :
        token_type(token_type),
        line_no(0),
        contents(contents),
        token_name(token_name) {};


    std::string repr();
    std::string normalized();
    std::uint16_t to_uint16_t();
};

}}

typedef std::vector<galaxy::jupiter::Token*> token_vector;

#endif
