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
        SpecWord,
        Operator,
        Braces,
        Literal,
        Number,
        Id,
        Escape,
        Default,
        Preproc,
        Comment,
        EndLine,
        Error,
        End,
    };

public:
    Lexer(const std::string &filename);
    Lexer(const Lexer &) = delete;
    Lexer(Lexer &&) = delete;

    Lexer::TokenType get_token();
    std::string get_token_text() const { return m_lexeme; }
    std::string get_language() const { return language; }

private:
    enum class State
    {
        None,
        Number,
        Id,
        Literal,
        Operator,
        Other,
        Comment,
        MultilineComment,
        Preproc,
        Escape,
        End,
    };
    State m_state;
    std::string language;

    std::ifstream m_file;
    std::string m_lexeme;
    char m_ch;

    // костыль
    bool is_multicomment;

    std::set<std::string> m_keywords;
    std::set<std::string> m_special_words;
    std::set<char> m_operators;

private:
    void read_config();
    void set_state(State state);
    void get_next_char() { m_ch = m_file.get(); }
    bool end_of_file() { return m_file.eof(); }
};
