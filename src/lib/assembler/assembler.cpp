#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

#include <libasteroid.hpp>
#include <opcodes/opcodes.hpp>
#include <tokenizer/tokenizer.hpp>
#include <parser/parser.hpp>

#include "assembler.hpp"

std::unordered_map<std::string, std::uint16_t> galaxy::jupiter::assembler::find_symbols(OPCODE_VECTOR opcodes){
    std::cout << "First pass" << std::endl;

    std::unordered_map<std::string, std::uint16_t> symbol_map = {};
    int location_counter = 0;

    for (auto opcode = opcodes.begin(); opcode != opcodes.end(); ++opcode) {

        std::cout << "Opcode: ";
        std::cout << (*opcode)->repr() << std::endl;

        if ((*opcode)->getType() == "LabelOpcode"){
            galaxy::jupiter::opcodes::LabelOpcode* label_opcode = dynamic_cast<galaxy::jupiter::opcodes::LabelOpcode*>(*opcode);
            symbol_map[label_opcode->label] = location_counter;

        } else if ((*opcode)->getType() == "OrigOpcode"){
            galaxy::jupiter::opcodes::OrigOpcode* orig_opcode = dynamic_cast<galaxy::jupiter::opcodes::OrigOpcode*>(*opcode);
            location_counter = orig_opcode->location;

        } else if ((*opcode)->getType() == "FillOpcode"){
            location_counter += 1;

        } else if ((*opcode)->getType() == "BasicOpcode"){
            location_counter += 1;

        } else if ((*opcode)->getType() == "DATOpcode") {
            galaxy::jupiter::opcodes::DATOpcode* dat_opcode = dynamic_cast<galaxy::jupiter::opcodes::DATOpcode*>(*opcode);
            location_counter += dat_opcode->format().size();

        } else if ((*opcode)->getType() == "ExportOpcode"){
            continue;

        } else {
           throw UnknownOpcode((*opcode)->getType());
        }
    }
    return symbol_map;
}


galaxy::asteroid galaxy::jupiter::assembler::pass_two(
        OPCODE_VECTOR opcodes,
        std::unordered_map<std::string, std::uint16_t> symbol_map){

    std::cout << "Second pass" << std::endl;

    int location_counter;
    galaxy::asteroid objectfile;

    for (auto opcode = opcodes.begin(); opcode != opcodes.end(); ++opcode) {

        std::cout << "Opcode: ";
        std::cout << (*opcode)->repr() << std::endl;

        if ((*opcode)->getType() == "LabelOpcode"){
            continue;

        } else if ((*opcode)->getType() == "OrigOpcode"){
            galaxy::jupiter::opcodes::OrigOpcode* orig_opcode = dynamic_cast<galaxy::jupiter::opcodes::OrigOpcode*>(*opcode);
            location_counter = orig_opcode->location;
        //    objectfile.add_notes("Load Address", location_counter);

        } else if ((*opcode)->getType() == "FillOpcode"){
            //objectfile.add_notes("Initialize Mem", location_counter, (*opcode)->size);
            location_counter += 1;

        } else if ((*opcode)->getType() == "BasicOpcode"){
            galaxy::jupiter::opcodes::BasicOpcode* instruction_opcode = dynamic_cast<galaxy::jupiter::opcodes::BasicOpcode*>(*opcode);
            std::uint16_t mach_inst = instruction_opcode->assemble();
            objectfile.object_code.push_back(mach_inst);
            //objectfile.add_instr(location_counter, mach_inst);
            location_counter += 1;

        } else if ((*opcode)->getType() == "DATOpcode") {
            // std::uint16_t data = (*opcode)->original()->format();
            // objectfile.add_instr(location_counter)

        } else if ((*opcode)->getType() == "ExportOpcode"){
            auto export_opcode = dynamic_cast<galaxy::jupiter::opcodes::ExportOpcode*>(*opcode);

            for (auto label_name: export_opcode->label_names) {
                std::pair<std::string, std::uint16_t> pair;
                pair.first = label_name;
                pair.second = symbol_map[label_name];
                std::cout << pair.first << " -> " << pair.second << std::endl;
                objectfile.exported_labels.insert(pair);
            }

        } else {
            throw UnknownOpcode((*opcode)->getType());
        }
    }

    return objectfile;
}


const std::unordered_map<std::string, std::uint16_t> galaxy::jupiter::assembler::basic_opcodes ({
    {"SET", 0x01}, {"ADD", 0x02}, {"SUB", 0x03},
    {"MUL", 0x04}, {"MLI", 0x05}, {"DIV", 0x06},
    {"DVI", 0x07}, {"MOD", 0x08}, {"MDI", 0x09},
    {"AND", 0x0a}, {"BOR", 0x0b}, {"XOR", 0x0c},
    {"SHR", 0x0d}, {"ASR", 0x0e}, {"SHL", 0x0f},
    {"IFB", 0x10}, {"IFC", 0x11}, {"IFE", 0x12},
    {"IFN", 0x13}, {"IFG", 0x14}, {"IFA", 0x15},
    {"IFL", 0x16}, {"IFU", 0x17}, {"NOP", 0x18},
    {"NOP", 0x19}, {"ADX", 0x1a}, {"SBX", 0x1b},
    {"NOP", 0x1c}, {"NOP", 0x1d}, {"STI", 0x1e},
    {"STD", 0x1f}
});
