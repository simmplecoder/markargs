#ifndef COMPILER_TOKEN_HPP
#define COMPILER_TOKEN_HPP

#include <string>
#include <iosfwd>

namespace markargs
{

    class token
    {
    public:
        enum class token_type
        {
            NAME,
            NUMBER,
            OP,
            NONE, //for debug purposes
            START,
            END
        };

    private:
        token_type current_tp;
        std::string current_payload;
    public:
        token();
        token(token_type tp_, const std::string& payload_);

        token_type type() const;
        const std::string& payload() const;

        bool operator!();
        friend std::istream& operator>>(std::istream& is, markargs::token& tk);

    private:
        token_type classify(char c);
        bool is_operator(char c);
    };

    std::istream& operator>>(std::istream& is, markargs::token& tk);
    std::ostream& operator<<(std::ostream& os, const markargs::token& tk);

    inline bool operator==(const token& lhs, const token& rhs)
    {
        return lhs.type() == rhs.type() && lhs.payload() == rhs.payload();
    }

    inline bool operator!=(const token& lhs, const token& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif
