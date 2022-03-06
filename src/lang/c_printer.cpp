#include <iostream>
#include <fmt/color.h>
#include <stack>
#include <utility>
#include "lang/c_printer.h"


void C_Printer::end_line(int &line_num)
{
    std::cout << std::endl;
    if (line_num % (m_lines - 1) == 0)
    {
        std::cout << ":\r";
        char ch = getchar();
        if (ch == 'q')
            exit(0);
        std::cout << "\r" << std::setw(2) << ++line_num << " |  ";
    }
    else
    {
        std::cout << "\r" << std::setw(2) << ++line_num << " |  ";
    }
}

void C_Printer::print()
{
    std::stack<std::pair<Lexer::TokenType, std::string>> stack;

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
                end_line(line_num);
                break;
            case Lexer::TokenType::Lattice:
                while (token != Lexer::TokenType::Id && token != Lexer::TokenType::Keyword)
                {
                    fmt::print(fg(fmt::color::crimson), "{}", lex.get_token_text());
                    token = lex.get_token();
                }
                fmt::print(fg(fmt::color::crimson), "{}", lex.get_token_text());
                stack.push(std::make_pair(token, lex.get_token_text()));
                break;
            case Lexer::TokenType::Number:
                fmt::print(fg(fmt::color::slate_blue), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Comment:
                fmt::print(fg(fmt::color::green), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Operator:
                if (!stack.empty() && lex.get_token_text() == "<" && stack.top().second == "include")
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
                    if (!stack.empty() && stack.top().first == Lexer::TokenType::Id && lex.get_token_text() == "-")
                    {
                        stack.emplace(std::make_pair(token, lex.get_token_text()));
                    }
                    if (!stack.empty() && stack.top().first == Lexer::TokenType::Operator && lex.get_token_text() == ">")
                    {
                        stack.emplace(std::make_pair(token, lex.get_token_text()));
                    }
                    fmt::print(fg(fmt::color::salmon), "{}", lex.get_token_text());
                }
                break;
            case Lexer::TokenType::Literal:
            {
                if (!stack.empty() && stack.top().second == "include")
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
                if (token_text == "true" || token_text == "false" || token_text == "NULL")
                {
                    fmt::print(fg(fmt::color::slate_blue), "{}", lex.get_token_text());
                }
                else if (!stack.empty() && (m_preproc_names.find(stack.top().second) != m_preproc_names.end()))
                {
                    fmt::print(fg(fmt::color::plum), "{}", lex.get_token_text());
                    stack.pop();
                }
                else if (!stack.empty() && stack.top().second == "pragma")
                {
                    while (token != Lexer::TokenType::EndLine)
                    {
                        fmt::print(fg(fmt::color::plum), "{}", lex.get_token_text());
                        token = lex.get_token();
                    }
                    end_line(line_num);
                    stack.pop();
                }
                else if (!stack.empty() && (m_structs.find(stack.top().second) != m_structs.end()))
                {
                    fmt::print(fg(fmt::color::deep_pink), "{}", lex.get_token_text());
                    stack.pop();
                    m_types_tbl.emplace(lex.get_token_text());
                }
                else if (m_types_tbl.find(lex.get_token_text()) != m_types_tbl.end())
                {
                    fmt::print(fg(fmt::color::deep_pink), "{}", lex.get_token_text());
                }
                else
                {
                    if (!stack.empty() && (stack.top().second == "." || stack.top().second == ">"))
                    {
                        fmt::print(fg(fmt::color::green_yellow) | fmt::emphasis::italic, "{}", token_text);
                        if (stack.top().second == ">")
                            stack.pop();
                        stack.pop();
                        stack.pop();
                    }
                    else
                    {
                        std::cout << token_text;
                        stack.emplace(std::make_pair(token, token_text));
                    }
                }
                break;
            }
            case Lexer::TokenType::SpecWord:
                fmt::print(fg(fmt::color::orange), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Keyword:
                fmt::print(fg(fmt::color::sienna) | fmt::emphasis::bold, "{}", lex.get_token_text());
                if (m_structs.find(lex.get_token_text()) != m_structs.end())
                {
                    stack.emplace(std::make_pair(token, lex.get_token_text()));
                }
                break;
            case Lexer::TokenType::Type:
                fmt::print(fg(fmt::color::golden_rod), "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Escape:
                fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Error:
                fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "{}", lex.get_token_text());
                break;
            case Lexer::TokenType::Default:
                if (!stack.empty() && stack.top().first == Lexer::TokenType::Id && lex.get_token_text() == ".")
                {
                    stack.emplace(std::make_pair(token, lex.get_token_text()));
                    std::cout << lex.get_token_text();
                }
                else
                {
                    std::cout << lex.get_token_text();
                }
                break;
            case Lexer::TokenType::LBracket:
                if (!stack.empty() && (m_structs.find(stack.top().second) != m_structs.end()) && lex.get_token_text() == "{")
                {
                    stack.pop();
                }
            default:
                std::cout << lex.get_token_text();
        }
    }
}

/*
    мб лексема тип, в конфиг.
*/