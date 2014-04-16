%%{
    machine asm_grammar;

    not_colon = [^:];
    colon = ":";
    semicolon = ";";
    comma = ",";
    dot = ".";
    newline = "\n\r" | "\n";

    basic_opcode_prim =
        "SET"i | "ADD"i | "SUB"i | "MUL"i |
        "MLI"i | "DIV"i | "DVI"i | "MOD"i |
        "MDI"i | "AND"i | "BOR"i | "XOR"i |
        "SHR"i | "ASR"i | "SHL"i | "IFB"i |
        "IFC"i | "IFE"i | "IFN"i | "IFG"i |
        "IFA"i | "IFL"i | "IFU"i | "ADX"i |
        "SBX"i | "STI"i | "STD"i;

    special_opcode_prim = "JSR"i | "INT"i;

    dat = "DAT"i;
    export_token = "EXPORT"i; # "export" seems to be reserved
    import_token = "IMPORT"i;
    fill = "FILL"i;
    orig = "ORIG"i;

    registers = "A"i | "B"i | "C"i | "X"i | "Y"i | "Z"i | "I"i | "J"i;

    specials = "PC"i | "SP"i | "EX"i | "IA"i;

    decimal = digit+;
    hexadecimal = "0x"i xdigit+;

    label_name = (alnum | "_" | "-")+;

    not_newline = [^\n];

    # this is to handle strings, taken from;
    # http://numbers.brighterplanet.com/2012/08/21/how-to-parse-quotes-in-ragel/
    dquote = '"';
    not_dquote_or_escape = [^"\\];
    escaped_something = /\\./;
}%%
