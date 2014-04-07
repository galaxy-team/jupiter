#include <sstream>

#include "token.hpp"
#include "utils.hpp"

std::string galaxy::jupiter::Token::repr(){
    std::stringstream ss;
    ss << "<Token:";

    if (token_name == "")
        ss << token_name;
    else
        ss << token_type;

    ss << " on line " << line_no;
    ss << " \"" << galaxy::jupiter::char_repr(contents) << "\"";
    ss << ">";
    return ss.str();
}

std::string galaxy::jupiter::Token::normalized(){
    return galaxy::stolower(contents);
}


std::uint16_t galaxy::jupiter::Token::to_uint16_t() {
    return strtol(contents.c_str(), NULL, 0);
}
