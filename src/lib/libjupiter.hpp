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
#include <unordered_map>
#include <vector>

namespace galaxy {
    namespace jupiter {
        /**
         * an object_file object represents a relocatable piece of DCPU-16
         * assembly code.
         */
        struct object_file {
            /**
             * Key=std::string
             * this is a map indexed by strings, each representing a label.
             * examples are:
             *  @foo (an exported label)
             *  bar  (an unexported label)
             *
             * The labels are mapped to their *declaration points* in the
             * outputted DASM-16 code.
             */
            std::unordered_map<
                std::string,                            // Key
                std::vector<std::uint16_t>::size_type   // Value
            > exported_labels;

            /**
             * Key=std::string
             * this is a map indexed by integers, each representing a location
             * in DASM-16 code.
             * examples are:
             *  0x1042 (an exported label)
             *  0x0032 (an unexported label)
             *
             * The labels are mapped to the labels *used in those positions*.
             * In the actual DASM-16 code, any positions where non-local labels
             * are used will be set to 0 and will be added to this map.
             */
            std::unordered_map<
                std::vector<std::uint16_t>::size_type,  // Key
                std::string                             // Value
            > used_labels;
            std::vector<std::uint16_t> object_code;
        };

        object_file assemble(
            std::string::const_iterator begin,
            std::string::const_iterator end
        );
    }
}

#endif