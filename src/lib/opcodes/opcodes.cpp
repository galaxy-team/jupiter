#include <cstdint>
#include <string>
#include <bitset>

#include <glog/logging.h>

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
        auto value = galaxy::jupiter::assembler::values.at(concatenated);

        LOG(INFO) << "Found " << concatenated << " as value: " << value;

        return value;
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

// Does the actual parsing and assembling
galaxy::jupiter::opcodes::LiteralOpcode* galaxy::jupiter::opcodes::BasicOpcode::assemble(symbol_map symbols) {

    // hex( (0x1f << 10) ^ (0x0 << 4) ^ 0x1 )
    // returns 0x7c01
    // sample code as supplied by startling

    // hex(0x7c<<24 ^ 0x2<<20 ^ 0x1<<16 ^ 0x1)
    // returns 0x7c11f888
    // my own (revised) reference code

    // assert (
    //     self.attrs['name'] in basic_opcodes or
    //     self.attrs['name'] in special_opcodes
    // ), self.attrs['name']

    // In bits (in LSB-0 format), a basic instruction has the format:
        // aaaaaabbbbbooooo
    // will take the next word literally, unless otherwise specified
    std::uint16_t opcode;
    std::vector<std::uint16_t> words;

    LOG(INFO) << "Accessing: " << name;
    if (galaxy::jupiter::assembler::basic_opcodes.find(name) == galaxy::jupiter::assembler::basic_opcodes.end()) {
        throw galaxy::jupiter::assembler::UnknownOpcode(name);
    } else {
        opcode = galaxy::jupiter::assembler::basic_opcodes.at(name);
        LOG(INFO) << "Opcode: 0x" << std::hex << opcode;
    }

    std::uint16_t final = a->resolve_as_value(symbols);
    LOG(INFO) << "0b" << std::bitset<16>(final);
    final ^= b->resolve_as_value(symbols);
    LOG(INFO) << "0b" << std::bitset<16>(final);
    final ^= opcode;
    LOG(INFO) << "0b" << std::bitset<16>(final);

    LOG(INFO) << "0b1000100000000001 <- reference";

    words.push_back(final);

    return new LiteralOpcode(words, this);
}

std::string galaxy::jupiter::opcodes::SpecialOpcode::repr(){
    return makeRepr(
        "name=\"" + name +
        "\",a=\"" + a->repr() +
        "\""
    );
}

std::string galaxy::jupiter::opcodes::OrigOpcode::repr(){
    return makeRepr("location=0x" + tohex(location));
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
    std::string str_contents = join(label_names, ", ");
    return makeRepr("contents=\"" + str_contents + "\"");
}

galaxy::jupiter::opcodes::LiteralOpcode* galaxy::jupiter::opcodes::FillOpcode::format(){
    std::vector<std::uint16_t> v;
    for(std::uint16_t i=0; i<length; i++) {
        v.push_back(contents);
    }
    return new LiteralOpcode(v, this);
}
