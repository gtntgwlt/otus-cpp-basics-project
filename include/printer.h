#pragma once

#include "lexer.h"


class Printer
{
public:
    Printer(Lexer &lexer) : lex(lexer) {}

    void print();

private:
    Lexer &lex;
};

