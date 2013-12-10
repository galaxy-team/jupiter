#include <cstdint>
#include <string>
#include <bitset>

#include "opcodes.hpp"
#include "assembler/assembler.hpp"

std::string galaxy::jupiter::opcodes::Opcode::makeRepr(std::string vars){
    return "<" + getType() + " " + vars + ">";
}

std::uint16_t galaxy::jupiter::opcodes::Part::resolve_as_value(symbol_map symbols)  {
    // see if the concatenated version exists as a value
    std::string concatenated;
    for (auto it: sub_tokens) {
        concatenated += it->contents;
    }

    if (galaxy::jupiter::assembler::values.find(concatenated) != galaxy::jupiter::assembler::values.end()) {
        std::cout << "Found " << concatenated << " as value: " << galaxy::jupiter::assembler::values.at(concatenated) << std::endl;
        return galaxy::jupiter::assembler::values.at(concatenated);
    } else {
        return 0;
    }
}

std::string galaxy::jupiter::opcodes::LabelOpcode::repr(){
    return makeRepr("label=" + label);
}

std::string galaxy::jupiter::opcodes::BasicOpcode::repr(){
    return makeRepr(
        "name=\"" + name +
        "\",a=\"" + a->repr() +
        "\",b=\"" + b->repr() +
        "\""
    );
}

std::string galaxy::jupiter::opcodes::OrigOpcode::repr(){
    return makeRepr("location=" + std::to_string(location));
}

std::string galaxy::jupiter::opcodes::DATOpcode::repr(){
    return makeRepr("contents=\"" + contents + "\"");
}

galaxy::jupiter::opcodes::LiteralOpcode* galaxy::jupiter::opcodes::DATOpcode::format(){
    std::vector<std::uint16_t> v;
    for(std::uint16_t i=0; i<contents.length(); i++) {
        v.push_back(contents[i]);
    }
    return new LiteralOpcode(v, this);
}

std::string galaxy::jupiter::opcodes::ExportOpcode::repr(){
    std::string str_contents;
    for (auto it: label_names){
        str_contents += it + ", ";
    }
    str_contents = str_contents.substr(0, str_contents.length() - 2);
    return makeRepr("contents=\"" + str_contents + "\"");
}

galaxy::jupiter::opcodes::LiteralOpcode* galaxy::jupiter::opcodes::FillOpcode::format(){
    std::vector<std::uint16_t> v;
    for(std::uint16_t i=0; i<length; i++) {
        v.push_back(contents);
    }
    return new LiteralOpcode(v, this);
}
