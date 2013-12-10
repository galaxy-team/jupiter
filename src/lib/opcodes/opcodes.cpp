#include <cstdint>
#include <string>

#include "opcodes.hpp"

std::string galaxy::jupiter::opcodes::Opcode::makeRepr(std::string vars){
    return "<" + getType() + " " + vars + ">";
}

std::string galaxy::jupiter::opcodes::LabelOpcode::repr(){
    return makeRepr("label=" + label);
}

std::uint16_t galaxy::jupiter::opcodes::BasicOpcode::assemble(){ return 0;}
std::string galaxy::jupiter::opcodes::BasicOpcode::repr(){
    return makeRepr(
        "name=\"" + name +
        "\",a=\"" + a->repr() +
        "\",b=\"" + b->repr() +
        "\""
    );
}

std::string galaxy::jupiter::opcodes::OrigOpcode::getType(){ return "OrigOpcode"; }
std::string galaxy::jupiter::opcodes::OrigOpcode::repr(){
    return makeRepr("location=" + std::to_string(location));
}

std::string galaxy::jupiter::opcodes::DATOpcode::repr(){
    return makeRepr("contents=\"" + contents + "\"");
}

std::vector<std::uint16_t> galaxy::jupiter::opcodes::DATOpcode::format(){
    std::vector<std::uint16_t> v;
    return v;
}

std::string galaxy::jupiter::opcodes::ExportOpcode::repr(){
    std::string str_contents;
    for (auto it: label_names){
        str_contents += it + ", ";
    }
    return makeRepr("contents=\"" + str_contents.substr(0, str_contents.length() - 2) + "\"");
}

galaxy::jupiter::opcodes::LiteralOpcode* galaxy::jupiter::opcodes::FillOpcode::format(){
    std::vector<std::uint16_t> v;
    for(std::uint16_t i=0; i<length; i++) {
        v.push_back(contents);
    }
    return new LiteralOpcode(v, this);
}
