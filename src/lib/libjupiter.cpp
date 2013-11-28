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

#include <vector>
#include <iostream>

#include <libasteroid.hpp>
#include <tokenizer/tokenizer.hpp>
#include <parser/parser.hpp>
#include <opcodes/opcodes.hpp>
#include <assembler/assembler.hpp>

galaxy::asteroid galaxy::jupiter::assemble(
    std::string::const_iterator begin,
    std::string::const_iterator end
)
{
    // the original cannot be a reference; the others must refer to something, after all
    std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes = {};

    auto tokens = (new galaxy::jupiter::tokenizer(begin, end))->lex();

    auto parser = new galaxy::jupiter::parser::Parser(tokens.begin(), tokens.end());
    parser->parse(opcodes);

    for (auto it = opcodes.begin(); it != opcodes.end(); ++it){
        std::cout << (**it).repr() << std::endl;
    }

    auto symbol_map = galaxy::jupiter::assembler::find_symbols(opcodes);
    return galaxy::jupiter::assembler::pass_two(opcodes, symbol_map);
}
