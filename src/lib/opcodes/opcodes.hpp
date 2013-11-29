#include <cstdint>
#include <string>
#include <vector>

#ifndef _OPCODES_HPP
#define _OPCODES_HPP

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
        SpecialOpcode(std::string name, std::string a) : name(name), a(a) {};
        std::string name;
        std::string a;

        std::uint16_t assemble();
        std::string getType();
        std::string repr();
    };

    class BasicOpcode : public Opcode {
    public:
        BasicOpcode(std::string name, std::string a, std::string b) : name(name), a(a), b(b) {};
        std::string name;
        std::string a;
        std::string b;

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
}}}

#endif
