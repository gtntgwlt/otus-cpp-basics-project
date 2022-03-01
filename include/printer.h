#pragma once

#include "lexer.h"


class Printer
{
public:
    Printer(Lexer &lexer) : lex(lexer) {}

    virtual void print();

protected:
    Lexer &lex;
};

