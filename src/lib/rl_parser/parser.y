%token_type {galaxy::jupiter::Token*}
%extra_argument { opcode_vector *opcodes }

%include {
    #include <cassert>
    #include <cstdlib>

    #include <iostream>
    #include <string>
    #include <sstream>
    #include <algorithm>
    #include <iterator>

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

    opcodes->push_back(
        new galaxy::jupiter::opcodes::DATOpcode(con->contents)
    );
}

statement ::= DOT EXPORT export_list(label_list). {
    NN(label_list);

    // break up the list
    std::istringstream iss(label_list->contents);
    std::vector<std::string> exported_labels {
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{}
    };

    opcodes->push_back(
        new galaxy::jupiter::opcodes::ExportOpcode(exported_labels )
    );
}

export_list(A) ::= LABEL_NAME(B). { NN(B); A=B; }
export_list(A) ::= LABEL_NAME(B) export_clause(C). {
    NN(B); NN(C);

    A=B;
    B->contents += " " + C->contents + " ";
}
export_clause(A) ::= COMMA export_list(B). { NN(B); A=B; }

statement ::= DOT FILL number(content) number(number). {
    NN(content); NN(number);

    int num = strtol(number->contents.c_str(), NULL, 0);
    int filler = strtol(content->contents.c_str(), NULL, 0);
    opcodes->push_back(
        new galaxy::jupiter::opcodes::FillOpcode(filler, num)
    );
}

statement ::= DOT ORIG number(position). {
    NN(position);

    int position_num = strtol(position->contents.c_str(), NULL, 0);
    opcodes->push_back(
        new galaxy::jupiter::opcodes::OrigOpcode(position_num)
    );
}


// if we don't pass on the string, it gets destroyed
dat_content(A) ::= QUOTED_STRING(B).    { A=B; }
dat_content(A) ::= HEXADECIMAL(B).      { A=B; }
dat_content(A) ::= DECIMAL(B).          { A=B; }

part(A) ::= REGISTER(B). { A=B; }
part(A) ::= DECIMAL(B). { A=B; }
part(A) ::= HEXADECIMAL(B). { A=B; }
