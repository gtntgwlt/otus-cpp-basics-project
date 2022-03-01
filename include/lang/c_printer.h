#pragma once

#include "../printer.h"
#include "../lexer.h"
#include <iostream>

class C_Printer : public Printer
{
public:
    C_Printer(Lexer &lex) : Printer(lex) {}

    virtual void print();
};

