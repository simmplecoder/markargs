#include "token.hpp"
#include <istream>

markargs::token::token():
        current_tp(token_type::NONE)
{}

markargs::token::token(token_type tp_, const std::string& payload_) :
        current_tp(tp_),
        current_payload(payload_)
{}


markargs::token::token_type markargs::token::type() const
{
    return current_tp;
}

const std::string& markargs::token::payload() const
{
    return current_payload;
}

bool markargs::token::operator!()
{
    return current_tp == token_type::NONE;
}

markargs::token::token_type markargs::token::classify(char c)
{
    if (std::isalpha((unsigned char)c) || c == '_')
    {
        return token_type::NAME;
    }
    else if (std::isdigit((unsigned char) c))
    {
        return token_type::NUMBER;
    }
    else if (is_operator(c))
    {
        return token_type::OP;
    }
    else
    {
        return token_type::NONE;
    }
}

bool markargs::token::is_operator(char c)
{
    return c == '+' || c == '-' || c == '=';
}


std::istream& markargs::operator>>(std::istream& is, markargs::token& tk)
{
    static enum { WHITESPACE, INNAME, INNUM, DONE } state;
    markargs::token temp{};
    std::swap(tk, temp);
    using tt = markargs::token::token_type;
    for (state = WHITESPACE; static_cast<bool>(is) && state != DONE; ) {
        char ch = is.peek();
        switch (tk.classify(ch)) {
            case tt::NAME:
                switch (state) {
                    case WHITESPACE:
                        state = INNAME;
                        tk.current_tp = tt::NAME;
                        // deliberately fall through
                    case INNAME:
                        tk.current_payload.push_back(ch);
                        is.get();
                        break;
                    default:
                        state = DONE;
                        break;
                };
                break;

            case tt::NUMBER:
                switch (state) {
                    case WHITESPACE:
                        state = INNUM;
                        tk.current_tp = tt::NUMBER;
                        // deliberately fall through
                    case INNUM:
                    case INNAME:
                        tk.current_payload.push_back(ch);
                        is.get();
                        break;
                    default:
                        state = DONE;
                        break;
                }
                break;

            case tt::OP:
                switch (state) {
                    case WHITESPACE:
                        state = DONE;
                        tk.current_tp = tt::OP;
                        tk.current_payload.push_back(ch);
                        is.get();
                        break;
                    default:
                        state = DONE;
                        break;
                }
                break;

            case tt::NONE:
                switch (state) {
                    case WHITESPACE:
                        is.get();
                        break;
                    default:
                        state = DONE;
                        break;
                }
                break;
        }
    }
    return is;
}

std::ostream& markargs::operator<<(std::ostream& os, const markargs::token& tk)
{
    static const std::string optype[] { "name", "number", "operator", "!!NONE!!" };
    return os << "{" << optype[static_cast<int>(tk.type())] << " : " << tk.payload() << "}";
}