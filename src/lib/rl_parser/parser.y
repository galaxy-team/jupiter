%token_type {galaxy::jupiter::Token*}
%extra_argument { opcode_vector *opcodes }

%include {
    #include <iostream>
    #include <cassert>
    #include "parser.h"
    #include "opcodes/opcodes.hpp"
    //#define NDEBUG

    // NN == NOT NULL
    #define NN(x) assert(x != NULL);
}

%syntax_error {
    std::cout << "Syntax error." << std::endl;

    #ifndef NDEBUG
    std::cout << "error at token " << yyTokenName[yymajor] << std::endl;

    for(int i=1; i<=yypParser->yyidx; i++)
        std::cout << " " << yyTokenName[yypParser->yystack[i].major] << std::endl;

/*    printf(" | %s ] unexpected '%.*s'\n",
        yyTokenName[yymajor],
        (yymajor != 0 && TOKEN != NULL) ? strlen(TOKEN->value) : 7,
        (yymajor != 0 && TOKEN != NULL) ? TOKEN->value : "$ (EOF)"
    );*/
    #endif
}

%token_destructor { ParseARG_STORE; }

%parse_accept {
    std::cout << "Parsing completed" << std::endl;
}

%parse_failure {
    std::cout << "Giving up. Parser is hopelessly lost..." << std::endl;
}

%stack_overflow {
    std::cout << "Giving up. Parser stack overflow" << std::endl;
}



program ::= statement_list.

statement_list ::= /* empty */.
statement_list ::= statement_list statement.

statement ::= BASIC_OPCODE_LITERAL(name) part(b) COMMA part(a). {
    NN(name); NN(b); NN(a);

    opcodes->push_back(new galaxy::jupiter::opcodes::BasicOpcode(
            name->contents,
            new galaxy::jupiter::opcodes::Part(b),
            new galaxy::jupiter::opcodes::Part(a)
        )
    );
    ParseARG_STORE;
}

statement ::= SPECIAL_OPCODE_LITERAL(name) part(b). {
    NN(name); NN(b);

    opcodes->push_back(new galaxy::jupiter::opcodes::SpecialOpcode(
            name->contents,
            new galaxy::jupiter::opcodes::Part(b)
        )
    );
    ParseARG_STORE;
}

statement ::= COLON LABEL_NAME(name). {
    NN(name);

    opcodes->push_back(new galaxy::jupiter::opcodes::LabelOpcode(name->contents));
    ParseARG_STORE;
}

statement ::= DOT DAT dat_content(con). {
    NN(con);

    std::string contents = con->contents.substr(
        1, con->contents.length() - 2
    );

    opcodes->push_back(
        new galaxy::jupiter::opcodes::DATOpcode(contents)
    );
}

// if we don't pass on the string, it gets destroyed
dat_content(A) ::= QUOTED_STRING(B).    { A=B; }
dat_content(A) ::= HEXADECIMAL(B).      { A=B; }
dat_content(A) ::= DECIMAL(B).          { A=B; }

part(A) ::= REGISTER(B). { A=B; }
part(A) ::= DECIMAL(B). { A=B; }
part(A) ::= HEXADECIMAL(B). { A=B; }
