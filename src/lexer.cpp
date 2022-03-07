#include "lexer.h"
#include <iostream>
#include <algorithm>
#include <fmt/color.h>


/*
диапазон строк

считать нужные строки в файл, потом файл удалить
считать в буфер, но надо будет подставить функцию вместо гет_некст_чар. указатель на член класса
*/

const std::string path_to_lang_config = "configs/language/";
const std::string path_to_color_scheme = "configs/color/";

Lexer::Lexer(const std::string &filename) :
    m_file(filename), m_filename(filename), m_state(State::None), m_lexeme(""),
    m_is_multicomment(false), m_prev_state(State::None)
{
    if (!m_file.is_open())
    {
        fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "File {} is not open :(\n", filename);
        exit(-1);
    }
    read_config();
    get_next_char();
}

void Lexer::read_config()
{
    // здесь будет определяться какой конфиг выбрать
    m_language = "c";
    std::string filename = path_to_lang_config + "c.json";
    std::ifstream lang_info { filename };
    if (!lang_info.is_open())
    {
        fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "Config file {} is not open :(\n", filename);
    }
    json j_info;
    lang_info >> j_info;
    lang_info.close();

    for (auto it = j_info["keywords"].begin(); it != j_info["keywords"].end(); ++it)
    {
        std::string word = it.value();
        m_keywords.emplace(word);
    }
    for (auto it = j_info["types"].begin(); it != j_info["types"].end(); ++it)
    {
        std::string word = it.value();
        m_types.emplace(word);
    }
    for (auto it = j_info["operators"].begin(); it != j_info["operators"].end(); ++it)
    {
        std::string word = it.value();
        m_operators.emplace(word.at(0));
    }
}

void Lexer::set_state(State state)
{
    m_lexeme += m_ch;
    get_next_char();
    m_state = state;
}

Lexer::TokenType Lexer::get_id_type() const
{
    if (m_keywords.find(m_lexeme) != m_keywords.end())
    {
        return TokenType::Keyword;
    }
    else if (m_types.find(m_lexeme) != m_types.end())
    {
        return TokenType::Type;
    }
    return TokenType::Id;
}

Lexer::TokenType Lexer::read_literal(const char ch)
{
    if (end_of_file())
    {
        m_state = State::End;
        return TokenType::Literal;
    }
    if (m_ch == ch)
    {
        set_state(State::None);
        return TokenType::Literal;
    }
    else if (m_ch == '\\')
    {
        m_state = State::Escape;
        return TokenType::Literal;
    }
    return TokenType::Empty;
}

Lexer::TokenType Lexer::get_token()
{
    m_lexeme.clear();
    while (true)
    {
        switch (m_state)
        {
        case State::None:
            /* code */
            if (m_ch == '\n')
            {
                get_next_char();
                if (m_is_multicomment)
                    m_state = State::MultilineComment;
                return TokenType::EndLine;
            }
            if (isdigit(m_ch) || m_ch == '.')
            {
                set_state(State::Number);
                break;
            }
            if (isalpha(m_ch) || m_ch == '_')
            {
                set_state(State::Id);
                break;
            }
            if (m_ch == '\'')
            {
                m_prev_state = State::LiteralOne;
                set_state(State::LiteralOne);
                break;
            }
            if (m_ch == '"')
            {
                m_prev_state = State::LiteralTwo;
                set_state(State::LiteralTwo);
                break;
            }
            if (m_operators.find(m_ch) != m_operators.end())
            {
                if (m_ch == '/' && (m_file.peek() == '/' || m_file.peek() == '*'))
                {
                    set_state(State::Comment);
                    break;
                }
                set_state(State::Operator);
                break;
            }
            if (m_ch == '#')
            {
                m_state = State::Lattice;
                break;
            }
            if (m_ch == '(' || m_ch == '[' || m_ch == '{')
            {
                set_state(State::None);
                return TokenType::LBracket;
            }
            if (m_ch == ')' || m_ch == ']' || m_ch == ')')
            {
                set_state(State::None);
                return TokenType::RBracket;
            }
            if (end_of_file())
            {
                m_state = State::End;
                break;
            }
            set_state(State::None);
            return TokenType::Default;
        case State::End:
            return TokenType::End;
        case State::Number:
            // science view
            if (end_of_file())
            {
                m_state = State::End;
                return TokenType::Number;
            }
            if (isdigit(m_ch) || m_ch == '.')
            {
                set_state(State::Number);
            }
            else
            {
                m_state = State::None;
                if (std::count(m_lexeme.begin(), m_lexeme.end(), '.') > 1)
                    return TokenType::Error;
                else if (m_lexeme == ".")
                    return TokenType::Default;
                else
                    return TokenType::Number;
            }
            break;
        case State::Id:
            if (end_of_file())
            {
                m_state = State::End;
                return get_id_type();
            }
            if (isalnum(m_ch) || m_ch == '_')
            {
                set_state(State::Id);
                break;
            }
            m_state = State::None;
            return get_id_type();
        case State::LiteralOne:
        {
            TokenType token = read_literal('\'');
            if  (token != TokenType::Empty)
                return token;
            set_state(State::LiteralOne);
            break;
        }
        case State::LiteralTwo:
        {
            TokenType token = read_literal('"');
            if  (token != TokenType::Empty)
                return token;
            set_state(State::LiteralTwo);
            break;
        }
        case State::Escape:
            // сомнительное решение
            set_state(m_prev_state);
            set_state(m_prev_state);
            return TokenType::Escape;
        case State::Comment: // no for all languages
            if (end_of_file())
            {
                m_state = State::End;
                return TokenType::Comment;
            }
            if (m_ch == '/')
            {
                while (m_ch != '\n')
                {
                    m_lexeme += m_ch;
                    get_next_char();
                }
                m_state = State::None;
                return TokenType::Comment;
            }
            if (m_ch == '*')
            {
                set_state(State::MultilineComment);
                break;
            }
            break;
        case State::MultilineComment:
            if (end_of_file())
            {
                m_state = State::End;
                return TokenType::Comment;
            }
            m_is_multicomment = true;
            if (m_ch == '*' && m_file.peek() == '/')
            {
                m_is_multicomment = false;
                set_state(State::None);
                set_state(State::None);
                return TokenType::Comment;
            }
            if (m_ch == '\n')
            {
                m_state = State::None;
                return TokenType::Comment;
            }
            set_state(State::MultilineComment);
            break;
        case State::Operator:
            if (end_of_file())
            {
                m_state = State::End;
                return TokenType::Operator;
            }
            if (m_ch == '=' || m_ch == '+' || m_ch == '-')
            {
                set_state(State::None);
            }
            else
            {
                m_state = State::None;
            }
            return TokenType::Operator;
        case State::Lattice:
            if (end_of_file())
            {
                m_state = State::End;
                return TokenType::Lattice;
            }
            set_state(State::None);
            return TokenType::Lattice;
        }
        // case State::Preproc:
        //     if (end_of_file())
        //     {
        //         m_state = State::End;
        //         return TokenType::Preproc;
        //     }
        //     // придумать что-то с include
        //     if (isspace(m_ch))
        //     {
        //         m_state = State::None;
        //         return TokenType::Preproc;
        //     }
        //     set_state(State::Preproc);
        //     break;
        // }
    }
}


/*
синтаксис:
    директивы препроцессора
    объвления переменных (подкрашивать существующие) *скорее семантика
*/

