#include <string>

struct Token {
    Token(int token_type, std::string contents)
        : token_type(token_type), contents(contents), line_number(0) {
    };

    int line_number;
    int token_type;
    std::string contents;
};
