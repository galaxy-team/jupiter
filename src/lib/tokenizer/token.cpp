#include <string>
#include <algorithm>
#include "token.hpp"
#include "tokenizer.hpp"

std::string galaxy::jupiter::Token::repr(){
    return (
        "<Token:" + name + " \"" +
        galaxy::jupiter::char_repr(contents)
        + "\">"
    );
}

std::string galaxy::jupiter::Token::normalized(){
    // just lowercases the contents; much easier in python :/
    std::string normal = contents;
    std::transform(normal.begin(), normal.end(), normal.begin(), tolower);
    return normal;
}

std::uint16_t galaxy::jupiter::Token::to_uint16_t() {
    return strtol(contents.c_str(), NULL, 0);
}
