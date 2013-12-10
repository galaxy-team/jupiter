#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <thread>

#include "token.hpp"
#include "tokenizer.hpp"

bool galaxy::jupiter::tokenizer::end() {
    return _upto == _length;
}

std::string galaxy::jupiter::tokenizer::peek() {
    if (end()) {
        return "";
    } else {
        return tokens.substr(_upto, 1);
    }
}

char galaxy::jupiter::tokenizer::peek_char() {
    // peek returns a string one char long, so just grab that char
    return peek()[0];
}

std::string galaxy::jupiter::tokenizer::peek_repr() {
    std::string p = peek();
    return galaxy::jupiter::char_repr(p);
}

std::string galaxy::jupiter::char_repr(std::string p){
    if (p == "\n"){
        p = "\\n";
    } else if (p == "\r"){
        p = "\\r";
    }
    return p;
}


void galaxy::jupiter::tokenizer::step(){
    if (!end()) {
        _upto += 1;
    }
}

void galaxy::jupiter::tokenizer::white(){
    while (peek() != "") {
        if (PEEK_IS(WHITESPACE)){
            step();
        } else {
            break;
        }
    }
}

std::string galaxy::jupiter::tokenizer::word(){
    std::string s = "";
    if (peek() == "\n") {
        return s;
    }
    // if (peek() != "\n") {
    //     s = peek();
    //     step();
    // }

    while (peek() != "" && !PEEK_IS(WHITESPACE)){
        if (isalnum(peek_char())){
            s += peek();
        } else {
            return s;
        }
        step();
    }

    return s;
}

std::string galaxy::jupiter::tokenizer::punctuation(){
    // we'll only ever get one punctuation thing at a time
    std::string s = peek();
    step();
    return s;
}


std::string galaxy::jupiter::tokenizer::digit() {
    std::string n = "";
    while (peek() != "" && isdigit(peek_char())) {
        n += peek();
        step();
    }
    return n;
}

std::string galaxy::jupiter::tokenizer::hex() {
    std::string n = "";
    while (peek() != "" && isxdigit(peek_char())){
        n += peek();
        step();
    }
    return n;
}

std::string galaxy::jupiter::tokenizer::binary() {
    std::string n = "";
    while (peek() != "" && PEEK_IS(BINARY_CHARS)){
        n += peek();
        step();
    }
    return n;
}

std::string galaxy::jupiter::tokenizer::next_digit(std::string err) {
    std::string n = peek();
    step();

    if (peek() != "" || (!isdigit(peek_char()))) {
        throw galaxy::jupiter::TokenError(err);
    }

    return n;
}

std::string galaxy::jupiter::tokenizer::number() {
    std::string n = "";

    if (peek() == "-") {
        n += next_digit(MFNUMBER_MINUS);
    }

    n += digit();
    if (n == "0"){
        if (PEEK_IS(HEX_X)) {
            n += peek();
            step();
            n += hex();
        } else if (PEEK_IS(BINARY_B)){
            n += peek();
            step();
            n += binary();
        }
    }
    // else {

        // if (peek() != "" && peek() == "."){
        //     n += next_digit(MFNUMBER_DEC_POINT);
        //     n += digit();
        // }

        // if (peek() && peek() in ['e', 'E']) {
        //     n += peek()
        //     step()
        //     if not peek() or peek() not in ('+', '-'):
        //         raise ParseError(MFNUMBER_SCI)
        //     n += next_digit(ERRORS['mfnumber_sci'])
        //     n += digit()
        // }
    // }

    return n;
}

galaxy::jupiter::Token* galaxy::jupiter::tokenizer::value(std::uint16_t guid) {
    white();
    std::string contents, name;

    if (PEEK_IS(PUNCTUATION)){
        name = "punctuation";
        contents = punctuation();

    } else if (isdigit(peek_char())) {
        name = "number";
        contents = number();

    } else {
        name = "word";
        contents = word();
    }

    return new Token(name, contents, guid);
}

token_vector galaxy::jupiter::tokenizer::lex(){
    token_vector parsed_tokens;
    std::uint16_t line_no = 1;
    std::uint16_t guid = 0;

    while (!end()){
        white();
        parsed_tokens.push_back(value(guid++));
        parsed_tokens.back()->line_no = line_no;

        if (parsed_tokens.back()->contents == "\n") {
            line_no++;
        }
    }

    return parsed_tokens;
}

void galaxy::jupiter::tokenizer::load_token_string(std::string _tokens){
    std::cout << "Lexer initialized with: " << std::endl;
    std::cout << "##########" << std::endl;
    std::cout << _tokens;
    std::cout << "##########" << std::endl << std::endl;

    tokens = _tokens;
    _length = tokens.length();
    _upto = 0;
}
