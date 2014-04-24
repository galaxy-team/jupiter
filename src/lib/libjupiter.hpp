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
#include <libasteroid.hpp>

namespace galaxy {
    namespace jupiter {
        /**
         * an object_file object represents a relocatable piece of DCPU-16
         * assembly code.
         */
        galaxy::asteroid assemble(
            std::string::const_iterator begin,
            std::string::const_iterator end
        );
    }
}

#endif
