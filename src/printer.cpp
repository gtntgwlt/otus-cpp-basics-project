
#include <iostream>
#include <fmt/color.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "printer.h"

Printer::Printer(Lexer &lexer) : lex(lexer)
{
    // seems only linux part
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    m_lines = w.ws_row;
    m_width = w.ws_col;
}

void Printer::print()
{
    int line_num = 1;
    std::cout << "\n\n" << std::setw(2) << line_num << " |  ";
    while (true)
    {
        Lexer::TokenType token = lex.get_token();
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
            case Lexer::TokenType::Number:
                fmt::print(fg(fmt::color::slate_blue), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Operator:
                fmt::print(fg(fmt::color::salmon), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Literal:
                fmt::print(fg(fmt::color::magenta), "{}", lex.get_token_text());
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
}

