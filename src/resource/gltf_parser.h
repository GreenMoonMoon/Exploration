//
// Created by MoonMoon on 2022-02-11.
//
#include <fstream>
#include <string>

#ifndef EXPLORATION_GLTF_PARSER_H
#define EXPLORATION_GLTF_PARSER_H

enum class TokenType {
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    STRING,
    NUMBER,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    COMMA,
    BOOLEAN,
    NULL_TYPE,
    EOF_
};

struct Token {
    TokenType type;
    std::string raw;
};

class Lexer {
private:
    std::iostream &inStream;
public:
    Lexer(std::iostream &in): inStream(in){}

    std::string processString(){
        return std::string{};
    }

    void clearSpace(){
        auto char_ = inStream.get();
        do {
            char_ = inStream.get();
        }while(char_ == ' ');
        inStream.putback(static_cast<char>(char_));
    }

    Token next(){
        auto nextCharacter = inStream.peek();

        Token token{};
        switch (nextCharacter) {
            case ' ':
                clearSpace();
            case '\"':
                token.type = TokenType::STRING;
                token.raw = processString();
                break;
            case '{':
                token.type = TokenType::CURLY_OPEN;
                inStream.get();
                break;
            case '}':
                token.type = TokenType::CURLY_CLOSE;
                inStream.get();
                break;
            case '[':
                token.type = TokenType::ARRAY_OPEN;
                inStream.get();
                break;
            case ']':
                token.type = TokenType::ARRAY_CLOSE;
                inStream.get();
                break;
            case ',':
                token.type = TokenType::COMMA;
                inStream.get();
                break;
            case ':':
                token.type = TokenType::COLON;
                inStream.get();
                break;
            case EOF:
                token.type = TokenType::EOF_;
                break;
            default:
                token.type = TokenType::NULL_TYPE;
                inStream.get();
        }
        return token;
    }
};

class GLTFparser {

};

#endif //EXPLORATION_GLTF_PARSER_H
