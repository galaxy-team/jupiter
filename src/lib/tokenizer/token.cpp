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
    std::string normal = contents;
    std::transform(normal.begin(), normal.end(), normal.begin(), tolower);
    return normal;
}
