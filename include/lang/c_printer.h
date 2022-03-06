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
    void end_line(int &line_num);

private:
    std::set<std::string> m_types_tbl;
    std::set<std::string> m_func_tbl;
    std::set<std::string> m_preproc_names { "define", "undef", "if", "elif", "ifdef", "ifndef" };
    std::set<std::string> m_structs { "struct", "union", "enum" };
};

