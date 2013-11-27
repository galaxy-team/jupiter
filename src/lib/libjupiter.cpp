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

#include "libjupiter.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <iostream>

#include <libasteroid.hpp>
#include <tokenizer/token.hpp>
#include <opcodes/opcodes.hpp>
#include <assembler/assembler.hpp>

template<typename Iter, typename OutIter>
void tokenise(Iter begin, Iter end, OutIter dest);

template<typename Iter, typename OutIter>
void parse(Iter begin, Iter end, OutIter dest);


galaxy::asteroid galaxy::jupiter::assemble(
    std::string::const_iterator begin,
    std::string::const_iterator end
)
{
    std::vector<galaxy::jupiter::Token*> tokens;
    std::vector<galaxy::jupiter::opcodes::Opcode*> opcodes;

    tokenise(begin, end, std::back_inserter(tokens));
    parse(tokens.begin(), tokens.end(), std::back_inserter(opcodes));

    auto symbol_map = galaxy::jupiter::assembler::find_symbols(opcodes);
    return galaxy::jupiter::assembler::pass_two(opcodes, symbol_map);
}

template<typename Iter, typename OutIter>
void parse(Iter begin, Iter end, OutIter dest)
{
    auto parser = new galaxy::jupiter::parser::Parser(begin, end);
    auto opcodes = parser->parse();
    std::copy(
        opcodes.begin(),
        opcodes.end(),
        dest
    );
}

template<typename Iter, typename OutIter>
void tokenise(Iter begin, Iter end, OutIter dest)
{
    auto lexer = new galaxy::jupiter::tokenizer(begin, end);
    auto tokens = lexer->lex();

    std::copy(
        tokens.begin(),
        tokens.end(),
        dest
    );
}
