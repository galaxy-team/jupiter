#ifndef RL_PARSER_HPP
#define RL_PARSER_HPP

#include "opcodes/opcodes.hpp"

namespace galaxy { namespace jupiter { namespace parser {

class Scan {
public:
    Scan() : newlines(0), cs(0), act(0), ts(0), te(0), lparser(NULL) {};
    ~Scan();

    void init();
    opcode_vector execute(const char* data, size_t len);

    std::uint16_t newlines;

private:
    int cs;
    int act;
    const char* ts;
    const char* te;

    void* lparser;
};

opcode_vector parse(std::string input);

}}}

#endif
