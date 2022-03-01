#include <iostream>
#include <fmt/color.h>
#include <string>
#include "lexer.h"
#include "printer.h"


int main(int argc, const char** argv)
{
    if (argc <= 1)
    {
        std::cerr << "Filename needed" << std::endl;
        exit(1);
    }
    std::string filename = argv[1];
    Lexer lex(filename);
    Printer out(lex);
    out.print();

    std::cout << std::endl << std::endl;
    return 0;
}

