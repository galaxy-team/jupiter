%%{
    machine asm_grammar;

    colon = ":";
    semicolon = ";";

    label_name = alnum+;
    # label = colon label_name;

    comment = semicolon alnum*;

    basic_opcode_prim = "ADD" | "SET";
    special_opcode_prim = "JSR" | "INT";

    registers = "A" | "B" | "C" | "X" | "Y" | "Z" | "I" | "J";

    specials = "PC" | "SP" | "EX" | "IA";

    hex_number = "0x" xdigit*;
    decimal_number = digit*;

    # part = registers | hex_number | label_name;
    # a = part;
    # b = part;

    # basic_opcode = basic_opcode_prim b "," a;
    # special_opcode = special_opcode_prim b;
}%%
