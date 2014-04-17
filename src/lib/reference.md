Pass 1;
 * assign addresses to all statements in the program
 * save the values (addresses) assigned to all labels (include label and variable names) for use in Pass 2 (deal with forward references)
 * perform some processing of assembler directives  (eg. BYTE, RESW, these can affect address assignment)

Pass 2;
 * assemble instructions (generate opcode and look up addresses)
 * generate data values defined by BYTE, WORD
 * perform processing of assembler directives not done in pass 1
 * write the object program and the assembly listing


Revised;

Pass 1;
 Input: std::vector<opcode*> without literal_opcode's
 Process: parse everything that can be into literal_opcode's, without label values
 Output: std::vector<opcode*> with literal_opcode replacing those which can


Pass 1;
 Input: std::vector<opcode*> with literal_opcode's
 Process: collect labels, locations (returns the symbol_map)
 Output: symbol_map

Pass 2;
 Input: std::vector<opcode*>, symbol_map
 Process: recalculate literal_opcode's using the source attribute with the label values
 Output: object file
