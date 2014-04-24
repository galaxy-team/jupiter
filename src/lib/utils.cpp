#include <utils.hpp>


std::string galaxy::stolower(std::string original) {
    std::transform(
        original.begin(),
        original.end(),
        original.begin(),
        tolower
    );
    return original;
}

std::string galaxy::stoupper(std::string original) {
    std::transform(
        original.begin(),
        original.end(),
        original.begin(),
        toupper
    );
    return original;
}

std::string galaxy::jupiter::char_repr(std::string p){
    if (p == "\n"){
        p = "\\n";
    } else if (p == "\r"){
        p = "\\r";
    }
    return p;
}
