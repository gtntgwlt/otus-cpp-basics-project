#include <string>
#include <fstream>
#include <array>

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


private:
    const std::array<char, 13> ops { '+', '-', '/', '*', '%', '!', '>', '<', '=', '|', '&', '~', '^' };

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

    std::ifstream m_file;
    std::string m_lexeme;
    char m_ch;

    // костыль
    bool is_multicomment;

private:
    void set_state(State state);
    void get_next_char() { m_ch = m_file.get(); }
    bool end_of_file() { return m_file.eof(); }

};
