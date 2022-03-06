#pragma once

#include <string>
#include <fstream>
#include <array>
#include <set>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Lexer
{
public:
    enum class TokenType
    {
        Keyword,
        Type,
        SpecWord,
        Operator,
        LBracket,
        RBracket,
        Literal,
        Number,
        Id,
        Escape,
        Default,
        Preproc,
        Comment,
        EndLine,
        Lattice,
        Error,
        End,
        Empty,
    };

public:
    Lexer(const std::string &filename);
    Lexer(const Lexer &) = delete;
    Lexer(Lexer &&) = delete;

    Lexer::TokenType get_token();
    std::string get_token_text() const { return m_lexeme; }
    std::string get_language() const { return m_language; }

private:
    enum class State
    {
        None,
        Number,
        Id,
        LiteralOne,
        LiteralTwo,
        Operator,
        Other,
        Comment,
        MultilineComment,
        Preproc,
        Escape,
        Lattice,
        End,
    };
    State m_state;
    std::string m_language;

    std::ifstream m_file;
    std::string m_lexeme;
    char m_ch;

    // костыли
    bool m_is_multicomment;
    State m_prev_state;

    std::set<std::string> m_keywords;
    std::set<std::string> m_types;
    std::set<char> m_operators { '+', '-', '*', '/', '=' };

private:
    void read_config();
    void set_state(State state);
    void get_next_char() { m_ch = m_file.get(); }
    bool end_of_file() { return m_file.eof(); }
    TokenType get_id_type() const;
    TokenType read_literal(const char ch);
};
