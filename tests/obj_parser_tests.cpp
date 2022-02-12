//
// Created by MoonMoon on 2022-02-11.
//
#include "gtest/gtest.h"

#include "../src/resource/obj_parser.h"

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