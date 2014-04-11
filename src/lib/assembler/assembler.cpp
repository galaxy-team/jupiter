#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

#include <libasteroid.hpp>
#include <opcodes/opcodes.hpp>


#include "assembler.hpp"


#define CAST_OPCODE_AS(type) dynamic_cast<galaxy::jupiter::opcodes::type*>


symbol_map galaxy::jupiter::assembler::find_symbols(opcode_vector opcodes){
    symbol_map symbols;

    int address = 0;
    std::string opcode_type;

    for (auto opcode : opcodes) {
        std::cout << "Opcode: ";
        std::cout << opcode->repr() << std::endl;
        opcode_type = opcode->getType();

        if (opcode_type == "LabelOpcode"){
            auto label_opcode = CAST_OPCODE_AS(LabelOpcode)(opcode);
            symbols[label_opcode->label] = address;

        } else if (opcode_type == "OrigOpcode"){
            auto orig_opcode = CAST_OPCODE_AS(OrigOpcode)(opcode);
            address = orig_opcode->location;

        } else if (opcode_type == "FillOpcode"){
            auto fill_opcode = CAST_OPCODE_AS(FillOpcode)(opcode);
            address += fill_opcode->size();

        } else if (opcode_type == "BasicOpcode"){
            auto basic_opcode = CAST_OPCODE_AS(BasicOpcode)(opcode);
            address += basic_opcode->assemble(symbols)->size();

        } else if (opcode_type == "DATOpcode") {
            auto dat_opcode = CAST_OPCODE_AS(DATOpcode)(opcode);
            address += dat_opcode->format()->contents.size();

        } else if (opcode_type == "ExportOpcode"){
            continue;

        } else {
           throw UnknownOpcode(opcode_type);
        }
    }
    return symbols;
}


opcode_vector galaxy::jupiter::assembler::pass_two(opcode_vector opcodes, symbol_map symbols){
    galaxy::jupiter::opcodes::Opcode* op = NULL;
    std::string opcode_type;
    opcode_vector new_opcodes;


    for (auto opcode : opcodes) {
        op = NULL;
        opcode_type = opcode->getType();

        std::cout << "Opcode: ";
        std::cout << opcode->repr() << std::endl;

        if (opcode_type == "LabelOpcode" || opcode_type == "OrigOpcode"){
            // handled in the first pass
            continue;

        } else if (opcode_type == "FillOpcode"){
            auto fill_opcode = CAST_OPCODE_AS(FillOpcode)(opcode);
            op = fill_opcode->format();

        } else if (opcode_type == "BasicOpcode"){
            auto instruction_opcode = CAST_OPCODE_AS(BasicOpcode)(opcode);
            op = instruction_opcode->assemble(symbols);

        } else if (opcode_type == "DATOpcode") {
            auto dat_opcode = CAST_OPCODE_AS(DATOpcode)(opcode);
            op = dat_opcode->format();

        } else if (opcode_type == "ExportOpcode"){
            // will be handled in last pass
            op = opcode;

        } else {
            throw UnknownOpcode(opcode_type);
        }

        std::cout << op->repr() << std::endl;
        new_opcodes.push_back(op);
    }

    return new_opcodes;
}

galaxy::asteroid galaxy::jupiter::assembler::resolve_to_bytecode(opcode_vector opcodes, symbol_map symbols) {
    galaxy::asteroid objfile;

    for (auto opcode = opcodes.begin(); opcode != opcodes.end(); ++opcode) {
        std::cout << "Opcode: " << (*opcode)->repr() << std::endl;
        galaxy::jupiter::opcodes::LiteralOpcode* op = NULL;;

        if ((*opcode)->getType() == "LiteralOpcode") {
            op = dynamic_cast<galaxy::jupiter::opcodes::LiteralOpcode*>(*opcode);
        } else if ((*opcode)->getType() == "ExportOpcode") {
                    auto export_opcode = dynamic_cast<galaxy::jupiter::opcodes::ExportOpcode*>(*opcode);

            for (auto label_name: export_opcode->label_names) {
                std::pair<std::string, std::uint16_t> pair;
                pair.first = label_name;
                pair.second = symbols[label_name];
                std::cout << pair.first << " -> " << pair.second << std::endl;
                objfile.exported_labels.insert(pair);
            }
        } else {
            throw UnknownOpcode((*opcode)->getType());
        }

        if (op != NULL) {
            for (auto it: op->contents) {
                objfile.object_code.push_back(it);
            }
        }
    }

    return objfile;
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

const std::unordered_map<std::string, std::uint16_t> galaxy::jupiter::assembler::special_opcodes ({
    {"NOP", 0x00}, {"JSR", 0x01}, {"NOP", 0x02}, {"NOP", 0x03},
    {"NOP", 0x04}, {"NOP", 0x05}, {"NOP", 0x06}, {"HCF", 0x07},
    {"INT", 0x08}, {"IAG", 0x09}, {"IAS", 0x0a}, {"IAP", 0x0b},
    {"NOP", 0x0c}, {"NOP", 0x0d}, {"NOP", 0x0e}, {"NOP", 0x0f},
    {"HWN", 0x10}, {"HQN", 0x11}, {"HWI", 0x12}, {"NOP", 0x13},
    {"NOP", 0x14}, {"NOP", 0x15}, {"NOP", 0x16}, {"NOP", 0x17},
    {"NOP", 0x18}, {"NOP", 0x19}, {"NOP", 0x1a}, {"NOP", 0x1b},
    {"NOP", 0x1c}, {"NOP", 0x1d}, {"NOP", 0x1e}, {"NOP", 0x1f}
});

const std::unordered_map<std::string, std::uint16_t> galaxy::jupiter::assembler::values ({
    {"A", 0x00}, {"B", 0x01},
    {"C", 0x02}, {"X", 0x03},
    {"Y", 0x04}, {"Z", 0x05},
    {"I", 0x06}, {"J", 0x07},
    {"[A]", 0x08}, {"[B]", 0x09},
    {"[C]", 0x0a}, {"[X]", 0x0b},
    {"[Y]", 0x0c}, {"[Z]", 0x0d},
    {"[I]", 0x0e}, {"[J]", 0x0f},
    // 0x10-0x17: [next word + register] goes here
    {"POP", 0x18}, {"[SP++]", 0x18},
    {"PUSH", 0x18}, {"[--SP", 0x18},
    {"PEEK", 0x19}, {"[SP]", 0x19},
    {"[SP+[PC++]]", 0x1a}, {"[--SP]", 0x1a},
    {"SP", 0x1b}, {"PC", 0x1c},
    {"EX", 0x1d}, {"[PC++]", 0x1e},
    {"PC++", 0x1f},
});
