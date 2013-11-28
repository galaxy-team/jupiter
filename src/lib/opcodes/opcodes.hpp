#include <cstdint>
#include <string>
#include <vector>

#ifndef _OPCODES_HPP
#define _OPCODES_HPP

namespace galaxy {
    namespace jupiter {
        namespace opcodes {
            // std::unordered_map<std::string,int> galaxy::jupiter::opcodes::basic_opcodes;

            class Opcode {
            public:
                virtual ~Opcode() {}
                virtual std::string getType() = 0;
                virtual std::string repr() = 0;

                std::string makeRepr(std::string vars);
            };

            class LabelOpcode : public Opcode {
            public:
                LabelOpcode(std::string _label) {
                    label = _label;
                };
                std::string label;

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
                std::string getB() { return b; }

                std::uint16_t assemble();
                std::string getType();
                std::string repr();
            };

            class OrigOpcode : public Opcode {
            public:
                OrigOpcode(int location) : location(location) {};
                int location;

                std::string getType();
                std::string repr();
            };

            class DATOpcode : public Opcode {
            public:
                DATOpcode(std::string contents) : contents(contents) {};
                std::string contents;

                std::string getType();
                std::string repr();
                std::vector<std::uint16_t> format();
            };
        }
    }
}

#endif
