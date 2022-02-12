//
// Created by MoonMoon on 2022-02-11.
//
#include "gtest/gtest.h"

#include "../src/resource/gltf_parser.h"


TEST(GLTFlexer, BasicToken){
    std::stringstream ss;
    ss << "{[],}:";
    Lexer l{ss};
    Token t = l.next();
    EXPECT_EQ(t.type, TokenType::CURLY_OPEN);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::ARRAY_OPEN);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::ARRAY_CLOSE);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::COMMA);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::CURLY_CLOSE);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::COLON);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::EOF_);
}

TEST(GLTFlexer, WhiteSpaces){
    std::stringstream ss;
    ss << "{ }";
    Lexer l{ss};
    Token t = l.next();
    EXPECT_EQ(t.type, TokenType::CURLY_OPEN);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::CURLY_CLOSE);
    t = l.next();
    EXPECT_EQ(t.type, TokenType::EOF_);
}

TEST(GLTFlexer, StringToken){
    std::stringstream ss;
    ss << "\"test\"\"\"\"test space\"";
    Lexer l{ss};
    Token t = l.next();
    EXPECT_EQ(t.type, TokenType::STRING);
    EXPECT_EQ(t.raw, "test");
    l.next();
    EXPECT_EQ(t.type, TokenType::STRING);
    EXPECT_EQ(t.raw, "");
    l.next();
    EXPECT_EQ(t.type, TokenType::STRING);
    EXPECT_EQ(t.raw, "test space");
}

TEST(GLTFlexer, numberToken){
    std::stringstream ss;
    ss << "1, 2.0, 3.10, 40.2";
    Lexer l{ss};
    Token t = l.next();
    EXPECT_EQ(t.type, TokenType::NUMBER);
    EXPECT_EQ(t.raw, "1");
    l.next();
    l.next();
    EXPECT_EQ(t.type, TokenType::NUMBER);
    EXPECT_EQ(t.raw, "2.0");
    l.next();
    l.next();
    EXPECT_EQ(t.type, TokenType::NUMBER);
    EXPECT_EQ(t.raw, "3.10");
    l.next();
    l.next();
    EXPECT_EQ(t.type, TokenType::NUMBER);
    EXPECT_EQ(t.raw, "40.2");
}


TEST(GLTFlexer, NullToken){
    std::stringstream ss;
    ss << "null";
    Lexer l{ss};
    Token t = l.next();
    EXPECT_EQ(t.type, TokenType::NULL_TYPE);
}