#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include <libasteroid.hpp>
#include "opcodes/opcodes.hpp"
#include "tokenizer/tokenizer.hpp"
#include "parser/parser.hpp"

#include "assembler.hpp"

std::unordered_map<std::string, std::uint16_t> galaxy::jupiter::assembler::find_symbols(std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes){
    std::cout << "First pass" << std::endl;

    std::unordered_map<std::string, std::uint16_t> symbol_map = {};
    int location_counter = 0;

    for (auto it = opcodes.begin(); it != opcodes.end(); ++it) {
        galaxy::jupiter::opcodes::Opcode* opcode = *it;

        std::cout << "Opcode: ";
        std::cout << opcode->repr() << std::endl;

        if (opcode->getType() == "LabelOpcode"){
            galaxy::jupiter::opcodes::LabelOpcode* label_opcode = dynamic_cast<galaxy::jupiter::opcodes::LabelOpcode*>(*it);
            symbol_map[label_opcode->label] = location_counter;

        } else if (opcode->getType() == "OrigOpcode"){
            galaxy::jupiter::opcodes::OrigOpcode* orig_opcode = dynamic_cast<galaxy::jupiter::opcodes::OrigOpcode*>(*it);
            location_counter = orig_opcode->location;

        } else if (opcode->getType() == "FillOpcode"){
            location_counter += 1;

        } else if (opcode->getType() == "InstructionOpcode"){
            location_counter += 1;

        } else {
           throw std::exception();
        }
    }
    return symbol_map;
}

galaxy::asteroid galaxy::jupiter::assembler::pass_two(std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes, std::unordered_map<std::string, std::uint16_t> symbol_map){
    std::cout << "Second pass" << std::endl;

    int location_counter;
    galaxy::asteroid objectfile;

    for (auto it = symbol_map.begin(); it != symbol_map.end(); ++it){
        std::cout << "Label:" << std::string((*it).first) << std::endl;
        // objectfile.used_labels.emplace((*it).first);
    }

    for (auto it = opcodes.begin(); it != opcodes.end(); ++it) {
        galaxy::jupiter::opcodes::Opcode* opcode = *it;

        std::cout << "Opcode: ";
        std::cout << opcode->repr() << std::endl;

        if (opcode->getType() == "LabelOpcode"){
            continue;

        } else if (opcode->getType() == "OrigOpcode"){
            galaxy::jupiter::opcodes::OrigOpcode* orig_opcode = dynamic_cast<galaxy::jupiter::opcodes::OrigOpcode*>(opcode);
            location_counter = orig_opcode->location;
        //    objectfile.add_notes("Load Address", location_counter);

        } else if (opcode->getType() == "FillOpcode"){
            //objectfile.add_notes("Initialize Mem", location_counter, opcode->size);
            location_counter += 1;

        } else if (opcode->getType() == "InstructionOpcode"){
            galaxy::jupiter::opcodes::InstructionOpcode* instruction_opcode = dynamic_cast<galaxy::jupiter::opcodes::InstructionOpcode*>(opcode);
            double mach_inst = instruction_opcode->assemble();
            //objectfile.add_instr(location_counter, mach_inst);
            location_counter += 1;

        } else {
            throw std::exception();
        }
    }

    return objectfile;
}


// int main(int argv, char *argc[]) {
//     std::string filename("test.dasm");
//     std::string file_contents;
//     Lexer* lexer;
//     Parser* parser;
//     std::vector<Token*> tokens;

//     file_contents = get_file_contents(filename);
//     lexer = new Lexer(file_contents);
//     tokens = lexer->lex();

//     parser = new Parser(tokens);


//     for (auto it = tokens.begin(); it != tokens.end(); ++it){
//         std::cout << "Token: " << (*it)->repr() << std::endl;
//     }

//     std::cout << std::endl;

//     std::vector<Opcode*> opcodes;
//     opcodes.push_back(new LabelOpcode("loop"));
//     opcodes.push_back(new InstructionOpcode("ADD", "A", "0"));

//     std::unordered_map<std::string, std::uint16_t> symbol_map = find_symbols(opcodes);

//     galaxy::asteroid objectfile = pass_two(opcodes, symbol_map);
// }
