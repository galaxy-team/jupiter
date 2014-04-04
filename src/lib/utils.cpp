#include <utils.hpp>

std::string galaxy::tolower(std::string original) {
    std::transform(original.begin(), original.end(), original.begin(), tolower);
    return original;
}
