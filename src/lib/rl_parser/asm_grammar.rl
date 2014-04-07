%%{
    machine asm_grammar;

    colon = ":";
    semicolon = ";";

    basic_opcode_prim = "ADD" | "SET";
    special_opcode_prim = "JSR" | "INT";

    registers = "A" | "B" | "C" | "X" | "Y" | "Z" | "I" | "J";

    specials = "PC" | "SP" | "EX" | "IA";

    hex_number = "0x" xdigit*;
    decimal_number = digit*;


}%%
