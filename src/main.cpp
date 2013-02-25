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

#include <cstdint>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <libjupiter.hpp>
#include <libasteroid.hpp>

int main(int argc, char** argv)
{
    /// DECLARE INPUT AND OUTPUT FILENAMES.
    std::string in;
    std::string out;

    /// GET INPUT AND OUTPUT FILENAMES FROM COMMAND LINE ARGUMENTS
    // Test that we have the right number of arguments
    if (argc <= 1 || argc >= 4) {
        std::cerr << "Error: Invalid usage. Usage is `jupiter inputfile outputfile`"  << std::endl;
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
    std::string asm_code;
    {
        char ch;
        while (inf.read(&ch, 1)) {
            asm_code.push_back(ch);
        }
    }

    /// ASSEMBLE THE ASM
    galaxy::asteroid objfile = galaxy::jupiter::assemble(asm_code.begin(), asm_code.end());

    /// WRITE OUT TO OUTPUT FILE - sorry about the mess
    std::ofstream outf(out);
    std::uint16_t size;
    // write out object_file.exported_labels
    size = objfile.exported_labels.size();
    outf.write(reinterpret_cast<char*>(&size), sizeof(std::uint16_t));
    for (std::pair<std::string, std::uint16_t> pair : objfile.exported_labels) {
        const char *s = pair.first.c_str();
        outf.write(s, pair.first.size()+1);
        outf.write(reinterpret_cast<char*>(&pair.second), sizeof(std::uint16_t));
    }
    // write out object_file.imported_labels
    size = objfile.imported_labels.size();
    outf.write(reinterpret_cast<char*>(&size), sizeof(std::uint16_t));
    for (std::pair<std::uint16_t, std::string> pair : objfile.imported_labels) {
        const char *s = pair.second.c_str();
        outf.write(s, pair.second.size()+1);
        outf.write(reinterpret_cast<char*>(&pair.first), sizeof(std::uint16_t));
    }
    // write out object_file.used_labels
    size = objfile.used_labels.size();
    outf.write(reinterpret_cast<char*>(&size), sizeof(std::uint16_t));
    for (std::uint16_t address : objfile.used_labels) {
        outf.write(reinterpret_cast<char*>(&address), sizeof address);
    }
    // write out object_file.object_code
    size = objfile.object_code.size();
    outf.write(reinterpret_cast<char*>(&size), sizeof(std::uint16_t));
    for (std::uint16_t byte : objfile.object_code) {
        outf.write(reinterpret_cast<char*>(&byte), sizeof byte);
    }
}
