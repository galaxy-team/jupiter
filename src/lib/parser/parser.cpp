#include <vector>
#include <iostream>

#include "parser.hpp"
#include <opcodes/opcodes.hpp>
#include <opcodes/mappings.hpp>

// template<typename T>
// T pop_from(std::vector<T> v){
//     T item = v.front();
//     v.erase(v.begin());
//     return item;
// }

// galaxy::jupiter::Token* pop_from(std::vector<galaxy::jupiter::Token*> v){
//     galaxy::jupiter::Token* item = v.front();
//     v.erase(v.begin());
//     return item;
// }


std::vector<galaxy::jupiter::opcodes::Opcode*> galaxy::jupiter::parser::Parser::parse(){
    std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes;

    for (auto it = tokens.begin(); it != tokens.end(); ++it){
        std::cout << " " << (*it)->repr();
    }
    std::cout << std::endl;

    while (!tokens.empty()) {
        galaxy::jupiter::Token* token = tokens.front();
        tokens.erase(tokens.begin());

        galaxy::jupiter::opcodes::Opcode* op = NULL;

        // std::cout << "Parsing token: " << token->repr();
        if (token->contents == ":"){
            op = handle_label(token, tokens);

        } else if (token->name == "word"){
            // TODO: check if it is a valid instruction, and whether it is basic or complex

            if (token->contents == "ORIG"){
                auto mem_loco = tokens.front()->contents;
                auto location = strtol(mem_loco.c_str(), NULL, 0);

                tokens.erase(tokens.begin());
                op = new galaxy::jupiter::opcodes::OrigOpcode(location);

            } else if (token->contents == "FILL") {
                // pass by for the moment

            } else {

                std::string name = token->contents;
                std::string a = tokens.at(0)->contents;
                std::string b = tokens.at(2)->contents;
                tokens.erase(tokens.begin(), tokens.begin() + 3);
                op = new galaxy::jupiter::opcodes::InstructionOpcode(name, a, b);
            }
        } else if (token->contents == "\n") {
        } else if (token->contents == ";") {
            std::cout << " ; ";
            // nuke comments
            int newline_index = 0;
            do {
                newline_index += 1;
                std::cout << " >" << tokens.at(newline_index)->contents << "< ";
            } while (tokens.at(newline_index)->contents != "\n");
            tokens.erase(tokens.begin(), tokens.begin() + newline_index);
            std::cout << std::endl;

        } else {
            std::cout << "Number? " << token->contents << std::endl;
        }

        if (op != NULL){
            std::cout << op->repr() << std::endl;
            opcodes.push_back(op);
        }
    }
    return opcodes;
}
galaxy::jupiter::opcodes::LabelOpcode* galaxy::jupiter::parser::handle_label(HANDLER_SIGNATURE) {
    auto t = pop(tokens);

    if (t->name != "word"){
        throw galaxy::jupiter::parser::InvalidInstruction("Invalid label name", "");
    }

    return new galaxy::jupiter::opcodes::LabelOpcode(t->contents);
}
