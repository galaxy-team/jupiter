/*

This file is part of jupiter.

jupiter is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

jupiter is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with jupiter.  If not, see <http://www.gnu.org/licenses/>.

Your copy of the GNU General Public License should be in the
file named "LICENSE.txt".

*/

#include "lib/libjupiter.hpp"

#include <cctype>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    /// DECLARE INPUT AND OUTPUT FILENAMES.
    std::string in;
    std::string out;

    /// GET INPUT AND OUTPUT FILENAMES FROM COMMAND LINE ARGUMENTS
    // Test that we have the right number of arguments
    if (argc <= 1 || argc >= 4) {
        std::cerr << "Error: Invalid usage. Usage is \"jupiter inputfile outputfile\""  << std::endl;
        return -1;
    } else {
        // The input filename is always the first argument.
        in = argv[1];

        // If the output filename is unspecified, use a modified form of
        // the input filename.
        //
        // e.g. "jupiter boot.asm" is equivalent to "jupiter boot.asm boot.o"
        if (argc == 2) {
            // Strip the last file extension, and replace with ".o"
            out = in.substr(0, in.find_last_of('.')) + ".o";
        } 
        // Otherwise, we use the second argument as the output filename.
        else {
            out = argv[2];
        }
    }

    /// READ IN THE INPUT FILE
    std::ifstream inf(in);
    std::vector<std::string> asm_code;
    for (std::string s : asm_code) {
        std::getline(inf, s);
    }

    /// ASSEMBLE THE ASM
    std::vector<std::uint16_t> object_code = galaxy::jupiter::assemble(asm_code.begin(), asm_code.end());
    
    /// WRITE OUT TO OUTPUT FILE
    std::ofstream outf(out);
    for (std::uint16_t word : object_code) {
       outf.write(reinterpret_cast<char*>(&word)+1, sizeof (std::uint8_t));
       outf.write(reinterpret_cast<char*>(&word), sizeof (std::uint8_t));
    }
}