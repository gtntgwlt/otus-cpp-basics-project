#include <iostream>
#include <fmt/color.h>
#include <string>
#include "lexer.h"
#include <fstream>
#include <iomanip>



std::string tokens[]
{
    "Keyword",
    "SpecWord",
    "Operator",
    "Braces",
    "Literal",
    "Number",
    "Id",
    "Escape",
    "Default",
    "Preproc",
    "Comment",
    "EndLine",
    "End",
};


int main(int argc, const char** argv)
{
    if (argc <= 1)
    {
        std::cerr << "Filename needed" << std::endl;
        exit(1);
    }
    std::string filename = argv[1];
    Lexer lex(filename);

    // прочитать файл заранее и узнать количество строк в нем, чтобы определить ширину
    // если задан диапазон, то проверить заодно попадает ли в него

    int line_num = 1;
    std::cout << "\n\n" << std::setw(2) << line_num << " |  ";
    while (true)
    {
        Lexer::TokenType token = lex.get_token();
        //std::cout << tokens[static_cast<int>(token)] << " : " << lex.get_token_text() << std::endl;
        // if (token == Lexer::TokenType::EndLine)
        //     std::cout << std::endl;
        if (token == Lexer::TokenType::End)
            break;

        switch (token)
        {
            case Lexer::TokenType::EndLine:
                std::cout << std::endl;
                std::cout << std::setw(2) << ++line_num << " |  ";
                break;
            case Lexer::TokenType::Default:
                std::cout << lex.get_token_text();
                break;
            case Lexer::TokenType::Preproc:
                fmt::print(fg(fmt::color::crimson), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Number:
                fmt::print(fg(fmt::color::slate_blue), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Comment:
                fmt::print(fg(fmt::color::green), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Operator:
                fmt::print(fg(fmt::color::salmon), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Literal:
                fmt::print(fg(fmt::color::magenta), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::SpecWord:
                fmt::print(fg(fmt::color::orange), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Keyword:
                fmt::print(fg(fmt::color::sienna) | fmt::emphasis::bold, "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Escape:
                fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Error:
                fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "{}", lex.get_token_text());
                break;
            default:
                std::cout << lex.get_token_text();
        }
    }

    std::cout << std::endl << std::endl;
    return 0;
}

