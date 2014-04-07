#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "rl_parser.hpp"

#include "opcodes/opcodes.hpp"
#include "tokenizer/token.hpp"
#include "parser.cpp"
#include "parser.h"


std::string getStr(const char* beg, const char* end)
{
    return std::string(beg).substr(0, end-beg);
}

#define EMIT(token_type) emit(lparser, ts, te, token_type, opcodes);

void emit(void* lparser,
          const char* ts, const char* te,
          int token_type, opcode_vector opcodes) {

    auto token = new galaxy::jupiter::Token(
        token_type,
        getStr(ts, te),

        #ifndef NDEBUG
        yyTokenName[token_type]
        #endif
    );

    std::cout << "Emiting: " << token->repr() << std::endl;

    // tell the parser what we've got
    Parse(
        lparser,
        token_type,
        token,
        &opcodes
    );
}

%%{
    machine asm_parser;
    include asm_grammar "asm_grammar.rl";

    main := |*
        label_name =>           { EMIT(LABEL_NAME); };
        basic_opcode_prim =>    { EMIT(BASIC_OPCODE_LITERAL); };
        special_opcode_prim =>  { EMIT(SPECIAL_OPCODE_LITERAL); };
        semicolon =>            { EMIT(SEMICOLON); };
        colon =>                { EMIT(COLON); };
        dot =>                  { EMIT(DOT); };
        dat =>                  { EMIT(DAT); };

        dquote ( not_dquote_or_escape | escaped_something )* dquote => {
            EMIT(QUOTED_STRING);
        };

        # ignore spaces
        space;
    *|;

    write data;
}%%

galaxy::jupiter::parser::Scan::~Scan()
{
    ParseFree(lparser, free);
}

void galaxy::jupiter::parser::Scan::init()
{
    lparser = ParseAlloc(malloc);
    %% write init;
}

opcode_vector galaxy::jupiter::parser::Scan::execute(const char* data, size_t len)
{
    const char* p =     data;
    const char* pe =    data + len;
    const char* eof =   pe;

    opcode_vector opcodes;

    %% write exec;

    Parse(lparser, 0, NULL, &opcodes);

    return opcodes;
}

opcode_vector galaxy::jupiter::parser::parse(std::string input) {
    auto p = Scan();
    p.init();

    #ifndef NDEBUG
        ParseTrace(
            stderr,
            (char *)"> "
        );
    #endif

    return p.execute(
        input.c_str(),
        input.length()
    );
}
