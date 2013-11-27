#include <cstdint>
#include <string>

#include "opcodes.hpp"

std::string galaxy::jupiter::opcodes::Opcode::makeRepr(std::string vars){
    return "<" + getType() + " " + vars + ">";
}

std::string galaxy::jupiter::opcodes::LabelOpcode::getType(){ return "LabelOpcode"; };
std::string galaxy::jupiter::opcodes::LabelOpcode::repr(){
    return makeRepr("label=" + label);
}

std::uint16_t galaxy::jupiter::opcodes::InstructionOpcode::assemble(){ return 0;}
std::string galaxy::jupiter::opcodes::InstructionOpcode::getType(){ return "InstructionOpcode"; }
std::string galaxy::jupiter::opcodes::InstructionOpcode::repr(){
    return makeRepr("name=\"" + name + "\",a=\"" + a + "\",b=\"" + b + "\"");
}

std::string galaxy::jupiter::opcodes::OrigOpcode::getType(){ return "OrigOpcode"; }
std::string galaxy::jupiter::opcodes::OrigOpcode::repr(){
    return makeRepr("location=" + std::to_string(location));
}

std::string galaxy::jupiter::opcodes::DATOpcode::getType(){ return "DATOpcode"; }
std::string galaxy::jupiter::opcodes::DATOpcode::repr(){
    return makeRepr("contents=" + contents);
}
