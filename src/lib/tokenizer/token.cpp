#include <sstream>

#include "token.hpp"
#include "utils.hpp"

std::string galaxy::jupiter::Token::repr(){
    std::stringstream ss;
    ss << "<Token:" << name;
    ss << " on line " << line_no;
    ss << " \"" << galaxy::jupiter::char_repr(contents) << "\"";
    ss << ">";
    return ss.str();
}

std::string galaxy::jupiter::Token::normalized(){
    // just lowercases the contents; much easier in python :/
    return tolower(contents);
}


std::uint16_t galaxy::jupiter::Token::to_uint16_t() {
    return strtol(contents.c_str(), NULL, 0);
}
