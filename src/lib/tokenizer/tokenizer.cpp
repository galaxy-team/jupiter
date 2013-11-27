#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <thread>

#include "token.hpp"
#include "tokenizer.hpp"

class ParseError : std::exception {
public:
    ParseError(std::string what) : what(what) {};
    // ~ParseError throw() {};
    std::string what;
};

bool galaxy::jupiter::lexer::end() {
    return _upto == _length;
}

std::string galaxy::jupiter::lexer::peek() {
    if (end()) {
        return "";
    } else {
        return tokens.substr(_upto, 1);
    }
}

bool galaxy::jupiter::lexer::is_digit() {
    return PEEK_IS(NUMBERS);
}

void galaxy::jupiter::lexer::step(){
    if (!end()) {
        _upto += 1;
        // return peek();
    }
}

void galaxy::jupiter::lexer::white(){
    while (peek() != "") {
        if (PEEK_IS(WHITESPACE)){
            step();
        } else {
            break;
        }
    }
}

std::string galaxy::jupiter::lexer::word(){
    std::string s = "";
    if (peek() == "\n") {
        return s;
    }
    // if (peek() != "\n") {
    //     s = peek();
    //     step();
    // }

    while (peek() != "" && !PEEK_IS(WHITESPACE)){
        if (PEEK_IS(ALPHANUM)){
            s += peek();
        } else {
            return s;
        }
        step();
    }

    return s;
};

std::string galaxy::jupiter::lexer::punctuation(){
    // we'll only ever get one punctuation thing at a time
    std::string s = peek();
    step();
    return s;
}


std::string galaxy::jupiter::lexer::digit() {
    std::string n = "";
    while (peek() != "" && is_digit()) {
        n += peek();
        step();
    }
    return n;
}

std::string galaxy::jupiter::lexer::hex() {
    std::string n = "";
    while (peek() != "" && (PEEK_IS(HEX_CHARS) || is_digit())){
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

std::string galaxy::jupiter::lexer::next_digit(std::string err) {
    std::string n = peek();
    step();

    if (peek() != "" || (!is_digit())) {
        throw ParseError(err);
    }

    return n;
}

std::string galaxy::jupiter::lexer::number() {
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

galaxy::jupiter::Token* galaxy::jupiter::lexer::value() {
    white();
    std::string contents, name;

    if (IN_SET(peek(), PUNCTUATION)){
        name = "punctuation";
        contents = punctuation();

    } else if (is_digit()) {
        name = "number";
        contents = number();

    } else {
        name = "word";
        contents = word();
    }

    return new Token(name, contents);
}

std::vector<galaxy::jupiter::Token*> galaxy::jupiter::lexer::lex(){
    std::vector<galaxy::jupiter::Token*> parsed_tokens;

    while (!end()){
        parsed_tokens.push_back(value());
        // std::cout << "Token: " << parsed_tokens.back()->repr() << "PEEK: " << peek() << std::endl;
    }

    return parsed_tokens;
};
