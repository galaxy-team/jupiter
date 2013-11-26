#include <string>
#include "token.hpp"

std::string galaxy::jupiter::Token::repr(){
    std::string reprd_contents = contents;

    if (reprd_contents.find("\n") >= 0) {
        while(reprd_contents.find("\n") != -1){
            reprd_contents = reprd_contents.replace(
                reprd_contents.find("\n"),
                1, "\\n"
            );
        }
    }

    return "<Token:" + name + " \"" + reprd_contents + "\">";
}
