#ifndef COMPILER_TOKEN_HPP
#define COMPILER_TOKEN_HPP

#include <string>

namespace markargs
{

    struct token
    {
        enum class token_type
        {
            NAME,
            NUMBER,
            OP,
            NONE //for debug purposes
        };

        token_type tp;
        std::string payload;

        token() :
                tp(token_type::NONE)
        {}

        token(token_type tp_, const std::string& payload_) :
                tp(tp_),
                payload(payload_)
        {}
    };

    inline bool operator==(const token& lhs, const token& rhs)
    {
        return lhs.tp == rhs.tp && lhs.payload == rhs.payload;
    }

    inline bool operator!=(const token& lhs, const token& rhs)
    {
        return !(lhs == rhs);
    }
}

#endif
