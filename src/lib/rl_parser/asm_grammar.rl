%%{
    machine asm_grammar;

    colon = ":";
    semicolon = ";";
    comma = ",";
    dot = ".";

    basic_opcode_prim = "ADD" | "SET";
    special_opcode_prim = "JSR" | "INT";

    dat = "DAT";

    registers = "A" | "B" | "C" | "X" | "Y" | "Z" | "I" | "J";

    specials = "PC" | "SP" | "EX" | "IA";

    decimal = digit+;
    hexadecimal = "0x" xdigit+;

    label_name = (alnum | "_" | "-")+;

    # this is to handle strings, taken from;
    # http://numbers.brighterplanet.com/2012/08/21/how-to-parse-quotes-in-ragel/
    dquote = '"';
    not_dquote_or_escape = [^"\\];
    escaped_something = /\\./;
}%%
