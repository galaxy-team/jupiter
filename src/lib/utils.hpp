#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

namespace galaxy {
    std::string stolower(std::string original);
    std::string stoupper(std::string original);

    // http://stackoverflow.com/a/9279620/1433288
    template <typename T>
    std::string join(const T& v, const std::string& delim) {
        std::ostringstream s;
        for (const auto& i : v) {
            if (&i != &v[0]) {
                s << delim;
            }
            s << i;
        }
        return s.str();
    }

    template<typename T>
    std::string tohex(T i) {
        std::stringstream ss;
        ss << std::hex << i;
        return ss.str();
    }

    namespace jupiter {
        std::string char_repr(std::string p);
    }
}

#endif
