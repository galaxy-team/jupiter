
#include <cstdint>
#include <assert.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

#ifndef _OPCODES_HPP
#define _OPCODES_HPP

// forward declare the opcodes
namespace galaxy { namespace jupiter { namespace opcodes {
    class basic_opcode;
    class dat_opcode;
    class export_opcode;
    class fill_opcode;
    class label_opcode;
    class literal_opcode;
    class opcode;
    class orig_opcode;
    class part;
    class special_opcode;
}}}
typedef std::vector<galaxy::jupiter::opcodes::opcode*> opcode_vector;
typedef std::unordered_map<std::string, std::uint16_t> symbol_map;

// before the includes that use them :P
#include "tokenizer/token.hpp"
#include <utils.hpp>


namespace galaxy { namespace jupiter { namespace opcodes {
    class opcode {
    public:
        opcode() {};

        virtual ~opcode() {};
        virtual std::string getType() = 0;
        virtual std::string repr() = 0;

        std::string makeRepr(std::string vars);

        bool operator== (opcode *Ref) {
            return Ref->repr() == repr();
        }
    };

    // the basic_opcode, dat_opcode, and special_opcode all end up
    // being one of these (literal_opcodes)
    class literal_opcode : public opcode {
    public:
        literal_opcode(std::vector<std::uint16_t> contents, opcode* source) : contents(contents), source(source) {};

        virtual ~literal_opcode() {};

        std::uint16_t size() { return contents.size(); }
        std::string getType() { return "literal_opcode"; }

        std::string repr() {
            std::stringstream ss;
            ss << "from " << source->repr() << " -> ";

            for (auto it: contents){
                ss << "0x" << std::hex << it << ", ";
            }

            std::string return_val(ss.str());
            return makeRepr(return_val.substr(0, return_val.length() - 2));
        }

        std::vector<std::uint16_t> contents;
        opcode* source = NULL;
    };

    class part {
    public:
        virtual ~part() {};
        part(token_vector sub_tokens, bool is_reference) : sub_tokens(sub_tokens), is_reference(is_reference) {};
        part(galaxy::jupiter::token* token) : is_reference(false) {
            sub_tokens.push_back(token);
        };

        token_vector sub_tokens;

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

    class label_opcode : public opcode {
    public:
        label_opcode(std::string label) : label(label) {};
        std::string label;

        virtual ~label_opcode() {};

        std::string getType(){ return "label_opcode"; }
        std::string repr();
    };

    class special_opcode : public opcode {
    public:
        special_opcode(std::string name, part* a) : name(name), a(a) {};
        std::string name;
        part* a;

        virtual ~special_opcode(){};

        literal_opcode* assemble(symbol_map symbols);
        std::string getType(){ return "special_opcode"; };
        std::string repr();
    };

    class basic_opcode : public opcode {
    public:
        basic_opcode(std::string name, part* a, part* b)
            : name(galaxy::stoupper(name)), a(a), b(b) {};
        std::string name;
        part* a;
        part* b;

        virtual ~basic_opcode() {};

        literal_opcode* assemble(symbol_map symbols);
        std::string getType(){ return "basic_opcode"; }
        std::string repr();


    };

    class orig_opcode : public opcode {
    public:
        orig_opcode(int location) : location(location) {};
        int location;

        virtual ~orig_opcode() {};

        std::string getType(){ return "orig_opcode"; }
        std::string repr();
    };

    class dat_opcode : public opcode {
    public:
        dat_opcode(std::string contents) : contents(contents) {};
        std::string contents;

        virtual ~dat_opcode() {};

        std::string getType(){ return "dat_opcode"; }
        std::string repr();
        literal_opcode* format();
    };

    class export_opcode : public opcode {
    public:
        export_opcode(std::vector<std::string> label_names) : label_names(label_names) {};
        std::vector<std::string> label_names;

        virtual ~export_opcode() {};

        std::string getType(){ return "export_opcode"; }
        std::string repr();
    };

    // functionally identical to export_opcode
    class import_opcode : public export_opcode {
    public:
        import_opcode(std::vector<std::string> label_names) : export_opcode(label_names) {};
        std::string getType(){ return "import_opcode"; }
    };

    class fill_opcode : public opcode {
    public:
        fill_opcode(std::uint16_t contents, std::uint16_t length) : length(length), contents(contents) {};
        std::uint16_t length;
        std::uint16_t contents;

        virtual ~fill_opcode() {};

        std::string getType() { return "fill_opcode"; }
        std::string repr() {
            std::stringstream ss;
            ss << "for " << length << " of \"" << contents << "\"";
            return makeRepr(ss.str());
        }

        // if fill just generates a sequence of sixteen bit numbers,
        // then the size is just the length
        std::uint16_t size() { return length; }
        literal_opcode* format();
    };
}}}

#endif
