#pragma once

#include <iostream>
#include <set>
#include "../printer.h"
#include "../lexer.h"


class C_Printer : public Printer
{
public:
    C_Printer(Lexer &lex) : Printer(lex) {}

    virtual void print();

private:
    std::set<std::string> preproc_names { "define", "undef", "if", "elif", "ifdef", "ifndef" };
};

