#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <algorithm>

namespace galaxy {
    std::string stolower(std::string original);
    std::string stoupper(std::string original);
    namespace jupiter {
        std::string char_repr(std::string p);
    }
}

#endif
