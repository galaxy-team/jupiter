#ifndef _TOKEN_HPP
#define _TOKEN_HPP

#include <vector>

namespace galaxy {
    namespace jupiter {
        class Token {
        public:
            std::string contents = "";
            std::string name;
            std::uint16_t line_no;
            std::uint16_t guid;
            Token(std::string name, std::string contents) : contents(contents), name(name), line_no(0) {};
            Token(std::string name, std::string contents, std::uint16_t guid) : contents(contents), name(name), guid(guid) {};

            std::string repr();
            std::string normalized();
            std::uint16_t to_uint16_t();
        };
    }
}

typedef std::vector<galaxy::jupiter::Token*> token_vector;

#endif
