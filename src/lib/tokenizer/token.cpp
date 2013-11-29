#include <string>
#include <algorithm>
#include "token.hpp"

std::string galaxy::jupiter::Token::repr(){
    std::string reprd_contents = contents;


    if (reprd_contents == "\n"){
        reprd_contents = "\\n";
    }

    return "<Token:" + name + " \"" + reprd_contents + "\">";
}

std::string galaxy::jupiter::Token::normalized(){
    std::string normal = contents;
    std::transform(normal.begin(), normal.end(), normal.begin(), tolower);
    return normal;
}
