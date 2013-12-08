#ifndef _TOKEN_HPP
#define _TOKEN_HPP

namespace galaxy {
    namespace jupiter {
        class Token {
        public:
            std::string contents = "";
            std::string name;
            Token(std::string name, std::string contents) : contents(contents), name(name) {};

            std::string repr();
            std::string normalized();
            std::uint16_t to_uint16_t();
        };
    }
}

#endif
