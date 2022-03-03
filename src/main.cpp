#include <iostream>
#include <fmt/color.h>
#include <string>
#include "lexer.h"
#include "printer_common.h"

/*
    мб предобработка файла тут. узнать язык, посчитать количество строк
    в лекс передать инфо об языке для загрузки конфига
*/

int main(int argc, const char** argv)
{
    if (argc <= 1)
    {
        std::cerr << "Filename needed" << std::endl;
        exit(1);
    }
    std::string filename = argv[1];
    Lexer lex(filename);
    Printer *out; // do smart pointer
    if (lex.get_language() == "c")
        out = new C_Printer(lex);
    else
        out = new Printer(lex);

    out->print();

    delete out;
    std::cout << std::endl << std::endl;
    return 0;
}

