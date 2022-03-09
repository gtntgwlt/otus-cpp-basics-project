#include <iostream>
#include <fmt/color.h>
#include <fmt/format.h>
//#include <ncurses/ncurses.h>
#include <stack>
#include <utility>
#include "lang/c_printer.h"


void C_Printer::print_line_string(int &line_num)
{
    fmt::print(fg(fmt::color::gray), "⁚{}⁚  ", fmt::format("{:^5}", ++line_num));
}

void C_Printer::end_line(int &line_num)
{
    static int last_line = -2;
    std::cout << std::endl;

    if (last_line + m_lines - 2 == line_num)
    {
        fmt::print(fg(fmt::color::gray), "⁚{}⁚  ", fmt::format("{:^5}", std::string({"▼"})));

        char ch = getchar();
        if (ch == 'q')
            exit(0);
        print_line_string(line_num);
        last_line = line_num;
    }
    else
    {
        print_line_string(line_num);
    }
}

void C_Printer::print()
{
    std::cout << std::endl;
    fmt::print(fg(fmt::color::gray), "{}", fmt::format("{:.^{}}", " " + lex.get_filename() + " ", m_width));

    std::stack<std::pair<Lexer::TokenType, std::string>> stack;

    int line_num = 0;
    fmt::print(fg(fmt::color::gray), "\n⁚{}⁚  \n", fmt::format("{:^5}", std::string()));
    print_line_string(line_num);
    while (true)
    {
        Lexer::TokenType token = lex.get_token();
        std::string token_text = lex.get_token_text();
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
                    fmt::print(fg(fmt::color::tomato), "{}", token_text);
                    token = lex.get_token();
                    token_text = lex.get_token_text();
                }
                fmt::print(fg(fmt::color::tomato), "{}", token_text);
                stack.push(std::make_pair(token, token_text));
                break;
            case Lexer::TokenType::Number:
                fmt::print(fg(fmt::color::slate_blue), "{}", token_text);
                break;
            case Lexer::TokenType::Comment:
                fmt::print(fg(fmt::color::green), "{}", token_text);
                break;
            case Lexer::TokenType::Operator:
                if (!stack.empty() && token_text == "<" && stack.top().second == "include")
                {
                    while ((token_text = lex.get_token_text()) != ">")
                    {
                        fmt::print(fg(fmt::color::yellow_green), "{}", token_text);
                        token = lex.get_token();
                    }
                    fmt::print(fg(fmt::color::yellow_green), "{}", token_text);
                    stack.pop();
                }
                else
                {
                    if (!stack.empty() && stack.top().first == Lexer::TokenType::Id && token_text == "-")
                    {
                        stack.emplace(std::make_pair(token, token_text));
                    }
                    if (!stack.empty() && stack.top().first == Lexer::TokenType::Operator && token_text == ">")
                    {
                        stack.emplace(std::make_pair(token, token_text));
                    }
                    fmt::print(fg(fmt::color::salmon), "{}", token_text);
                }
                break;
            case Lexer::TokenType::Literal:
            {
                if (!stack.empty() && stack.top().second == "include")
                {
                    fmt::print(fg(fmt::color::yellow_green), "{}", token_text);
                    stack.pop();
                }
                else
                {
                    fmt::print(fg(fmt::color::light_green), "{}", token_text);
                }
                break;
            }
            case Lexer::TokenType::Id:
            {
                if (token_text == "true" || token_text == "false" || token_text == "NULL")
                {
                    fmt::print(fg(fmt::color::slate_blue), "{}", token_text);
                }
                else if (!stack.empty() && (m_preproc_names.find(stack.top().second) != m_preproc_names.end()))
                {
                    fmt::print(fg(fmt::color::plum), "{}", token_text);
                    stack.pop();
                }
                else if (!stack.empty() && stack.top().second == "pragma")
                {
                    while (token != Lexer::TokenType::EndLine)
                    {
                        fmt::print(fg(fmt::color::plum), "{}", token_text);
                        token = lex.get_token();
                        token_text = lex.get_token_text();
                    }
                    end_line(line_num);
                    stack.pop();
                }
                else if (!stack.empty() && (m_structs.find(stack.top().second) != m_structs.end()))
                {
                    fmt::print(fg(fmt::color::pale_violet_red), "{}", token_text);
                    stack.pop();
                    m_types_tbl.emplace(token_text);
                }
                else if (m_types_tbl.find(token_text) != m_types_tbl.end())
                {
                    fmt::print(fg(fmt::color::pale_violet_red), "{}", token_text);
                }
                else if (m_func_tbl.find(token_text) != m_func_tbl.end())
                {
                    fmt::print(fg(fmt::color::violet), "{}", token_text);
                }
                else
                {
                    if (!stack.empty() && (stack.top().second == "." || stack.top().second == ">"))
                    {
                        fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::italic, "{}", token_text);
                        if (stack.top().second == ">")
                            stack.pop();
                        stack.pop();
                        if (!stack.empty() && stack.top().first == Lexer::TokenType::Id)
                            stack.pop();
                    }
                    else
                    {
                        Lexer::TokenType n_token = lex.get_token();
                        std::string n_token_text = lex.get_token_text();
                        // there may be spaces, but not today
                        if (n_token_text == "(")
                        {
                            Lexer::TokenType n_token2 = lex.get_token();
                            std::string n_token_text2 = lex.get_token_text();
                            if (n_token2 == Lexer::TokenType::Keyword || n_token2 == Lexer::TokenType::Type ||
                                m_types_tbl.find(n_token_text2) != m_types_tbl.end() || n_token_text2 == ")")
                            {
                                m_func_tbl.emplace(token_text);
                                fmt::print(fg(fmt::color::violet), "{}", token_text);
                                lex.put_token(n_token2, n_token_text2);
                                lex.put_token(n_token, n_token_text);
                                break;
                            }
                            else
                            {
                                lex.put_token(n_token2, n_token_text2);
                                lex.put_token(n_token, n_token_text);
                            }
                        }
                        else
                        {
                            lex.put_token(n_token, n_token_text);
                        }

                        std::cout << token_text;
                        stack.emplace(std::make_pair(token, token_text));
                    }
                }
                break;
            }
            case Lexer::TokenType::Keyword:
                fmt::print(fg(fmt::color::medium_violet_red) | fmt::emphasis::bold, "{}", token_text);
                if (m_structs.find(token_text) != m_structs.end())
                {
                    stack.emplace(std::make_pair(token, token_text));
                }
                break;
            case Lexer::TokenType::Type:
                fmt::print(fg(fmt::color::golden_rod), "{}", token_text);
                break;
            case Lexer::TokenType::Escape:
                fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "{}", token_text);
                break;
            case Lexer::TokenType::Error:
                fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "{}", token_text);
                break;
            case Lexer::TokenType::Default:
                if (/*!stack.empty() && stack.top().first == Lexer::TokenType::Id && */ token_text == ".")
                {
                    stack.emplace(std::make_pair(token, token_text));
                }
                std::cout << token_text;
                break;
            case Lexer::TokenType::LBracket:
                if (!stack.empty() && (m_structs.find(stack.top().second) != m_structs.end()) && token_text == "{")
                {
                    stack.pop();
                }
            default:
                std::cout << token_text;
        }
    }
}
