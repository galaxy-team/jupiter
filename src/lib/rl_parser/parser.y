%token_type {galaxy::jupiter::Token*}
%extra_argument { opcode_vector *opcodes }

%include {
    #include <iostream>
    #include <cassert>
    #include "parser.h"
    #include "opcodes/opcodes.hpp"
    //#define NDEBUG
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

%parse_accept {
    std::cout << "Parsing completed" << std::endl;
}

%parse_failure {
    std::cout << "Giving up.  Parser is hopelessly lost..." << std::endl;
}


%stack_overflow {
    std::cout << "Giving up.  Parser stack overflow" << std::endl;
}

program ::= statement_list.

statement_list ::= /* empty */.
statement_list ::= statement_list statement.

statement ::= BASIC_OPCODE_LITERAL(name) B(b) COMMA A(a). {
    opcodes->push_back(new BasicOpcode(name->contents, b->contents, a->contents));
    ParseARG_STORE;
}

statement ::= SPECIAL_OPCODE_LITERAL(name) B(b). {
    opcodes->push_back(new SpecialOpcode(name->contents, b->contents));
    ParseARG_STORE;
}

statement ::= COLON LABEL_NAME(name). {
    opcodes->push_back(new LabelOpcode(name->contents));
    ParseARG_STORE;
}

statement ::= SEMICOLON comment NEWLINE.
statement ::= SEMICOLON comment.

comment ::= /* empty */.
comment ::= COMMENT comment.
