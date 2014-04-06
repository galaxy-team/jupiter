#ifndef OPCODE_H
#define OPCODE_H

#include <sstream>
#include <vector>

class Opcode {
public:
    virtual std::string getType() = 0;
    virtual std::string repr() = 0;
};

class BasicOpcode : public Opcode {
public:
    BasicOpcode(std::string op, std::string a, std::string b) : op(op), a(a), b(b) {}
    std::string op;
    std::string a;
    std::string b;

    std::string getType() { return "BasicOpcode"; }

    std::string repr()
    {
        std::stringstream ss;
        ss << "<BasicOpcode ";
        ss << "op=\"" << op << "\" ";
        ss << "a=\"" << a << "\" ";
        ss << "b=\"" << b << "\">";
        return ss.str();
    }
};

class SpecialOpcode : public Opcode {
public:
    SpecialOpcode(std::string op, std::string b) : op(op), b(b) {
    };
    std::string op;
    std::string b;

    std::string getType() { return "SpecialOpcode"; };
    std::string repr(){
        std::stringstream ss;
        ss << "<SpecialOpcode ";
        ss << "op=\"" << op << "\" ";
        ss << "b=\"" << b << "\">";
        return ss.str();
    }
};

class LabelOpcode : public Opcode {
public:
    LabelOpcode(std::string name) : name(name) {};
    std::string name;

    std::string getType(){
        return "LabelOpcode";
    }

    std::string repr(){
        std::stringstream ss;
        ss << "<LabelOpcode name=\"" << name << "\">";
        return ss.str();
    }
};

typedef std::vector<Opcode*> opcode_vector;

#endif
