#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

#ifndef _OPCODES_HPP
#define _OPCODES_HPP

// forward declare the opcodes
namespace galaxy { namespace jupiter { namespace opcodes {
    class BasicOpcode;
    class DATOpcode;
    class ExportOpcode;
    class FillOpcode;
    class LabelOpcode;
    class LiteralOpcode;
    class Opcode;
    class OrigOpcode;
    class Part;
    class SpecialOpcode;
}}}
typedef std::vector<galaxy::jupiter::opcodes::Opcode*> opcode_vector;
typedef std::unordered_map<std::string, std::uint16_t> symbol_map;

// before the includes that use them :P
#include "tokenizer/token.hpp"
#include <utils.hpp>

namespace galaxy { namespace jupiter { namespace opcodes {
    class Opcode {
    public:
        Opcode() {};

        virtual ~Opcode() {};
        virtual std::string getType() = 0;
        virtual std::string repr() = 0;

        std::string makeRepr(std::string vars);
    };

    // the BasicOpcode, DATOpcode, and SpecialOpcode all end up
    // being one of these (LiteralOpcodes)
    class LiteralOpcode : public Opcode {
    public:
        LiteralOpcode(std::vector<std::uint16_t> contents, Opcode* source) : contents(contents), source(source) {};

        virtual ~LiteralOpcode() {};

        std::uint16_t size() { return contents.size(); }
        std::string getType() { return "LiteralOpcode"; }

        std::string repr() {
            std::stringstream ss;
            ss << "from " << source->repr() << " -> ";
            for (auto it: contents){
                ss  << "0x" << std::hex << it << ", ";
            }
            std::string return_val(ss.str());
            return makeRepr(return_val.substr(0, return_val.length() - 2));
        }

        std::vector<std::uint16_t> contents;
        Opcode* source = NULL;
    };

    class Part {
    public:
        virtual ~Part() {};
        Part(std::vector<galaxy::jupiter::Token*> sub_tokens, bool is_reference) : sub_tokens(sub_tokens), is_reference(is_reference) {};
        std::vector<galaxy::jupiter::Token*> sub_tokens;

        bool is_reference;

        std::uint16_t resolve_as_value(symbol_map symbols);

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
        LabelOpcode(std::string label) {
            label = tolower(label);
        };
        std::string label;

        virtual ~LabelOpcode() {};

        std::string getType(){ return "LabelOpcode"; }
        std::string repr();
    };

    class SpecialOpcode : public Opcode {
    public:
        SpecialOpcode(std::string name, Part* a) : name(name), a(a) {};
        std::string name;
        Part* a;

        virtual ~SpecialOpcode(){};

        LiteralOpcode* assemble(symbol_map symbols);
        std::string getType(){ return "SpecialOpcode"; };
        std::string repr();
    };

    class BasicOpcode : public Opcode {
    public:
        BasicOpcode(std::string name, Part* a, Part* b) : name(name), a(a), b(b) {};
        std::string name;
        Part* a;
        Part* b;

        virtual ~BasicOpcode() {};

        LiteralOpcode* assemble(symbol_map symbols);
        std::string getType(){ return "BasicOpcode"; }
        std::string repr();
    };

    class OrigOpcode : public Opcode {
    public:
        OrigOpcode(int location) : location(location) {};
        int location;

        virtual ~OrigOpcode() {};

        std::string getType(){ return "OrigOpcode"; }
        std::string repr();
    };

    class DATOpcode : public Opcode {
    public:
        DATOpcode(std::string contents) : contents(contents) {};
        std::string contents;

        virtual ~DATOpcode() {};

        std::string getType(){ return "DATOpcode"; }
        std::string repr();
        LiteralOpcode* format();
    };

    class ExportOpcode : public Opcode {
    public:
        ExportOpcode(std::vector<std::string> label_names) : label_names(label_names) {};
        std::vector<std::string> label_names;

        virtual ~ExportOpcode() {};

        std::string getType(){ return "ExportOpcode"; }
        std::string repr();
    };

    class FillOpcode : public Opcode {
    public:
        FillOpcode(std::uint16_t contents, std::uint16_t length) : length(length), contents(contents) {};
        std::uint16_t length;
        std::uint16_t contents;

        virtual ~FillOpcode() {};

        std::string getType() { return "FillOpcode"; }
        std::string repr() {
            std::stringstream ss;
            ss << "of " << length << " for \"" << contents << "\"";
            return makeRepr(ss.str());
        }

        // if fill just generates a sequence of sixteen bit numbers,
        // then the size is just the length
        std::uint16_t size() { return length; }
        LiteralOpcode* format();
    };
}}}

#endif
