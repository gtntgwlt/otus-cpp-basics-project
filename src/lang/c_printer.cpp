#include <iostream>
#include <fmt/color.h>
#include <stack>
#include "lang/c_printer.h"


void C_Printer::print()
{
    std::stack<std::string> stack;

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
            case Lexer::TokenType::Lattice:
                while (token != Lexer::TokenType::Id && token != Lexer::TokenType::Keyword)
                {
                    fmt::print(fg(fmt::color::crimson), "{}", lex.get_token_text());
                    token = lex.get_token();
                }
                fmt::print(fg(fmt::color::crimson), "{}", lex.get_token_text());
                stack.push(lex.get_token_text());
                break;
            case Lexer::TokenType::Number:
                fmt::print(fg(fmt::color::slate_blue), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Comment:
                fmt::print(fg(fmt::color::green), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Operator:
                if (!stack.empty() && lex.get_token_text() == "<" && stack.top() == "include")
                {
                    while (lex.get_token_text() != ">")
                    {
                        fmt::print(fg(fmt::color::yellow_green), "{}", lex.get_token_text());
                        token = lex.get_token();
                    }
                    fmt::print(fg(fmt::color::yellow_green), "{}", lex.get_token_text());
                    stack.pop();
                }
                else
                {
                    fmt::print(fg(fmt::color::salmon), "{}", lex.get_token_text());
                }
                break;
            case Lexer::TokenType::Literal:
            {
                if (!stack.empty() && stack.top() == "include")
                {
                    fmt::print(fg(fmt::color::yellow_green), "{}", lex.get_token_text());
                    stack.pop();
                }
                else
                {
                    fmt::print(fg(fmt::color::magenta), "{}", lex.get_token_text());
                }
                break;
            }
            case Lexer::TokenType::Id:
            {
                std::string token_text = lex.get_token_text();
                if (token_text == "true" || token_text == "false")
                {
                    fmt::print(fg(fmt::color::slate_blue), "{}", lex.get_token_text());
                }
                else if (!stack.empty() && (preproc_names.find(stack.top()) != preproc_names.end()))
                {
                    fmt::print(fg(fmt::color::plum), "{}", lex.get_token_text());
                    stack.pop();
                }
                else if (!stack.empty() && stack.top() == "pragma")
                {
                    while (token != Lexer::TokenType::EndLine)
                    {
                        fmt::print(fg(fmt::color::plum), "{}", lex.get_token_text());
                        token = lex.get_token();
                    }
                    std::cout << std::endl << std::setw(2) << ++line_num << " |  ";
                    stack.pop();
                }
                else
                    std::cout << token_text;
                break;
            }
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
}

/*
    мб лексема тип, в конфиг.
*/