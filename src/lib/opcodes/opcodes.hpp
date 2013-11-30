#include <cstdint>
#include <string>
#include <vector>

#ifndef _OPCODES_HPP
#define _OPCODES_HPP

#include "tokenizer/token.hpp"

#define OPCODE_VECTOR std::vector<galaxy::jupiter::opcodes::Opcode*>&

namespace galaxy { namespace jupiter { namespace opcodes {
    class Opcode {
    public:
        Opcode() {};

        virtual ~Opcode() {}
        virtual std::string getType() = 0;
        virtual std::string repr() = 0;

        std::string makeRepr(std::string vars);
    };

    class Part {
    public:
        virtual ~Part() {};
        Part(std::vector<galaxy::jupiter::Token*> sub_tokens, bool is_reference) : sub_tokens(sub_tokens), is_reference(is_reference) {};
        std::vector<galaxy::jupiter::Token*> sub_tokens;
        bool is_reference;

        std::string repr() {
            std::string return_val;
            for (auto it: sub_tokens){
                return_val += it->repr() + ", ";
            }
            return return_val.substr(0, return_val.length() - 2);
        }
    };

    class LabelOpcode : public Opcode {
    public:
        LabelOpcode(std::string label) : label(label) {};
        std::string label;

        virtual ~LabelOpcode() {};

        std::string getType();
        std::string repr();
    };

    class SpecialOpcode : public Opcode {
    public:
        SpecialOpcode(std::string name, Part* a) : name(name), a(a) {};
        std::string name;
        Part* a;

        std::uint16_t assemble();
        std::string getType();
        std::string repr();
    };

    class BasicOpcode : public Opcode {
    public:
        BasicOpcode(std::string name, Part* a, Part* b) : name(name), a(a), b(b) {};
        std::string name;
        Part* a;
        Part* b;

        virtual ~BasicOpcode() {};

        std::uint16_t assemble();
        std::string getType();
        std::string repr();
    };

    class OrigOpcode : public Opcode {
    public:
        OrigOpcode(int location) : location(location) {};
        int location;

        virtual ~OrigOpcode() {};

        std::string getType();
        std::string repr();
    };

    class DATOpcode : public Opcode {
    public:
        DATOpcode(std::string contents) : contents(contents) {};
        std::string contents;

        virtual ~DATOpcode() {};

        std::string getType();
        std::string repr();
        std::vector<std::uint16_t> format();
    };

    class ExportOpcode : public Opcode {
    public:
        ExportOpcode(std::vector<std::string> label_names) : label_names(label_names) {};
        std::vector<std::string> label_names;

        virtual ~ExportOpcode() {};

        std::string getType();
        std::string repr();
        std::vector<std::uint16_t> format();
    };
}}}

#endif
