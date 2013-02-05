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

template<typename Iter, typename OutIter>
void tokenise(Iter begin, Iter end, OutIter dest);

auto galaxy::jupiter::assemble(
	std::string::const_iterator begin,
	std::string::const_iterator end
) -> object_file
{
	std::vector<std::string> tokens;
	tokenise(begin, end, std::back_inserter(tokens));
	for(auto iter = tokens.begin(); iter != tokens.end(); ++iter) {

	}

	object_file obj;
	return obj;
}

template<typename Iter, typename OutIter>
void tokenise(Iter begin, Iter end, OutIter dest)
{
	std::stringstream ss;
	std::copy(begin, end, std::ostream_iterator<char>(ss));
	std::copy(
		std::istream_iterator<std::string>(ss),
		std::istream_iterator<std::string>(),
		dest
	);
}
