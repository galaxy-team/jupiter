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

#ifndef LIBJUPITER_HPP
#define LIBJUPITER_HPP

#include <cstdint>
#include <string>
#include <vector>

namespace galaxy {
	namespace jupiter {
		/**
		 * assemble
		 * 
		 * @param begin   an iterator pointing to the beginning of a subsequence of a vector<string>
		 * @param end     an iterator pointing to just past the end of a subsequence of a vector<string>
		 * 
		 * assemble takes the iterators defining a sequence [begin, end) of strings, each representing
		 * a line of DCPU-16 assembly language code.
		 *
		 * TODO: generalise to support other containers - list<string>, etc.
		 */
		std::vector<std::uint16_t> assemble(
			std::vector<std::string>::const_iterator begin, 
			std::vector<std::string>::const_iterator end
		);


		/**
		 * assemble
		 * 
		 * @param begin   an iterator pointing to the beginning of a subsequence of a string
		 * @param end     an iterator pointing to just past the end of a subsequence of a string
		 * 
		 * assemble takes the iterators defining a sequence [begin, end) of characters, which
		 * together represent a line of DCPU-16 ASM code.
		 *
		 * assemble returns a vector of uint16_t, representing an instruction (which can be of variable
		 * length).
		 */
		std::vector<std::uint16_t> assemble(
			std::string::const_iterator begin, 
			std::string::const_iterator end
		);

		#if 0
		// Not yet implemented.
		std::vector<std::string> disassemble(
			std::vector<std::uint16_t>::const_iterator begin, 
			std::vector<std::uint16_t>::const_iterator end
		);
		#endif /* 0 */
	}
}

#endif /* LIBJUPITER_HPP */