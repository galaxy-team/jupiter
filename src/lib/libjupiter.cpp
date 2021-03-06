/*

This file is part of libjupiter.

libjupiter is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libjupiter is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with libjupiter.  If not, see <http://www.gnu.org/licenses/>.

Your copy of the GNU Lesser General Public License should be in the
file named "LICENSE-LGPL.txt".

*/

#include <libjupiter.hpp>

#include <iostream>

#include <glog/logging.h>

#include <libasteroid.hpp>
#include <rl_parser/rl_parser.hpp>
#include <assembler/assembler.hpp>

galaxy::asteroid galaxy::jupiter::assemble(
    std::string::const_iterator begin,
    std::string::const_iterator end
)
{
    opcode_vector opcodes;

    opcodes = galaxy::jupiter::parser::parse(
        std::string(begin, end)
    );

    for (auto it = opcodes.begin(); it != opcodes.end(); ++it){
        LOG(INFO) << (**it).repr() << std::endl;
    }

    LOG(INFO) << "First pass";
    auto symbol_map = galaxy::jupiter::assembler::find_symbols(opcodes);
    LOG(INFO) << "Second pass: " << opcodes.size();
    opcodes = galaxy::jupiter::assembler::pass_two(opcodes, symbol_map);
    LOG(INFO) << "Third pass: " << opcodes.size();

    return galaxy::jupiter::assembler::resolve_to_bytecode(opcodes, symbol_map);
}
