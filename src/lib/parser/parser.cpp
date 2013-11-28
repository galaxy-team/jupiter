#include <vector>
#include <iostream>

#include "parser.hpp"
#include <opcodes/opcodes.hpp>
#include <opcodes/mappings.hpp>


std::vector<galaxy::jupiter::opcodes::Opcode*> galaxy::jupiter::parser::Parser::parse(){
    std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes;

    for (auto it = tokens.begin(); it != tokens.end(); ++it){
        std::cout << " " << (*it)->repr();
    }
    std::cout << std::endl;

    while (!tokens.empty()) {
        auto token = pop(tokens);

        galaxy::jupiter::opcodes::Opcode* op = NULL;

        // std::cout << "Parsing token: " << token->repr();
        if (token->contents == ":"){
            op = handle_label(token, tokens);

        } else if (token->contents == "."){
            token = pop(tokens);

            if (token->normalized() == "dat"){
                op = handle_dat(token, tokens);

            } else {
                std::cout << token->repr() << std::endl;
                throw InvalidInstruction("Unknown instruction", token);
            }

        } else if (token->name == "word"){
            if (token->normalized() == "orig"){
                op = handle_orig(token, tokens);

            } else if (token->normalized() == "fill") {
                // pass by for the moment

            } else if (token->normalized() == "dat"){
                op = handle_dat(token, tokens);

            } else {
                // TODO: check if it is a valid instruction, and whether it is basic or complex
                op = handle_inst(token, tokens);
            }
        } else if (token->contents == "\n") {
            // just ignore newlines. this could admittely mean that you can have something like this;
            // ADD a,1 SUB a,1
            // and it would work fine...

        } else if (token->contents == ";") {
            handle_comments(token, tokens);
        } else {
            throw InvalidInstruction("Misplaced token: ", token->contents);
        }

        if (op != NULL){
            std::cout << op->repr() << std::endl;
            opcodes.push_back(op);
        }
    }
    return opcodes;
}

galaxy::jupiter::opcodes::OrigOpcode* galaxy::jupiter::parser::handle_orig(HANDLER_SIGNATURE){

    auto mem_loco = pop(tokens)->contents;
    auto location = strtol(mem_loco.c_str(), NULL, 0);

    return new galaxy::jupiter::opcodes::OrigOpcode(location);
}


galaxy::jupiter::opcodes::InstructionOpcode* galaxy::jupiter::parser::handle_inst(HANDLER_SIGNATURE) {

    std::string name = token->contents;
    std::string a = pop(tokens)->contents;

    // std::cout << name << a;

    // at index 1 is the comma... or at least there should be :P
    if (tokens.front()->contents != ","){
        throw galaxy::jupiter::parser::InvalidInstruction(
            "Invalid instruction; ", tokens.front()->repr()
        );
    } else {
        pop(tokens);
    }

    std::string b = pop(tokens)->contents;

    // if (pop(tokens)->contents)

    return new galaxy::jupiter::opcodes::InstructionOpcode(name, a, b);
}

void galaxy::jupiter::parser::handle_comments(HANDLER_SIGNATURE) {
    // nukes comments
    do {
        pop(tokens);
    } while (tokens.front()->contents != "\n");
}

galaxy::jupiter::opcodes::DATOpcode* galaxy::jupiter::parser::handle_dat(HANDLER_SIGNATURE) {
    std::string contents = "";

    // pop the opening quote
    pop(tokens);

    while (tokens.front()->contents != "\"" && (!tokens.size() != 1)) {
        contents += pop(tokens)->contents;
    }

    if (tokens.front()->contents != "\""){
        throw InvalidAssembly(".DAT missing closing quote.");
    }

    // pop the closing quote
    pop(tokens);

    return new galaxy::jupiter::opcodes::DATOpcode(contents);
}

galaxy::jupiter::opcodes::LabelOpcode* galaxy::jupiter::parser::handle_label(HANDLER_SIGNATURE) {
    auto t = pop(tokens);

    if (t->name != "word"){
        throw galaxy::jupiter::parser::InvalidInstruction("Invalid label name", "");
    }

    return new galaxy::jupiter::opcodes::LabelOpcode(t->contents);
}
