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
 * parse everything that can be into LiteralOpcode's, without label values

Pass 2;
 * collect labels, locations

Pass 3;
 * recalculate LiteralOpcode's using the source attribute with the label values
