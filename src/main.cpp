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

/* c stdlib */
#include <cstdint>

/* cpp stdlib */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/* application specific */
#include <libjupiter.hpp>
#include <libasteroid.hpp>

/* third party */
#include "OptionParser.h"


int main(int argc, char** argv)
{
   // setup the command line argument parser
    optparse::OptionParser parser = optparse::OptionParser()
        .description("Jupiter, Galaxy's assembler")
        .usage("usage: %prog [options] <input_filename> <output_filename>");

    // parse the buggers - Dom
    optparse::Values options = parser.parse_args(argc, argv);
    std::vector<std::string> args = parser.args();

    // declare input and output filenames.
    std::string in;
    std::string out;


    // Test that we have the right number of arguments
    if (args.empty()) {
        // if no positional (required) arguments were provided, print help and exit
        parser.print_help();
        return -1;
    } else {
        // The input filename is always the first argument.
        in = args[0];

        // We use the second argument as the output filename.

        if (args.size() == 1){
             // If the output filename is unspecified, use a modified form of
             // the input filename.
             //
             // e.g. "jupiter boot.asm" is equivalent to "jupiter boot.asm boot.o"

             // Strip the last file extension, and replace with ".o"
             out = in.substr(0, in.find_last_of('.')) + ".o";

        } else {
            // Otherwise, we use the second argument as the output filename.
            out = args[1];
        }
    }

    // read in the input file
    std::ifstream inf(in);
    std::string asm_code;
    {
        char ch;
        while (inf.read(&ch, 1)) {
            asm_code.push_back(ch);
        }
    }

    // assemble the asm
    galaxy::asteroid objfile = galaxy::jupiter::assemble(
        asm_code.begin(),
        asm_code.end()
    );

    std::ofstream outf(out);
    galaxy::asteroid_belt::write_obj(objfile, outf);
    outf.close();
}
