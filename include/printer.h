#pragma once

#include "lexer.h"


class Printer
{
public:
    Printer(Lexer &lexer);

    virtual void print();

protected:
    Lexer &lex;
    int m_lines;
};

