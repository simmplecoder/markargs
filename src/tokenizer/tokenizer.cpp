#include "tokenizer.hpp"
#include <memory>
#include <cctype>

namespace markargs
{
    tokenizer::tokenizer(std::istream& is) noexcept:
            stream(std::addressof(is))
    {}

    tokenizer::tokenizer(tokenizer&& other) noexcept:
            stream(other.stream)
    {
        other.stream = nullptr;
    }

    token tokenizer::read_identifier()
    {
        std::string current_identifier;
        char next_char;
        //no need to check, since this function is called from gigantic pile of ifs which means next_char is a letter
        *stream >> next_char;
        current_identifier += next_char;

        //numbers in identifiers are allowed if they are not leading
        while (*stream >> next_char && (std::isalnum((unsigned char) next_char) || next_char == '_'))
        {
            current_identifier += next_char;
        }

        stream->unget(); //sets badbit if eof, so no check for eof

        return token{token::token_type::NAME, current_identifier};
    }

    token tokenizer::read_number()
    {
        std::string current_number;
        char next_char = 0;
        while (*stream >> next_char && std::isdigit((unsigned char) next_char))
        {
            current_number += next_char;
        }

        stream->unget(); //sets badbit if eof, so no check for eof

        return token{token::token_type::NUMBER, current_number};
    }

    token tokenizer::read_operator()
    {
        char op;
        *stream >> op;
        return token{token::token_type::OP, std::string{op}};
    }

    bool tokenizer::is_operator(char c) const noexcept
    {
        return c == '+' || c == '-' || c == '=';
    }

    tokenizer::operator bool()
    {
        return state;
    }

    tokenizer& operator>>(tokenizer& t, token& tk)
    {
        auto& stream = *t.stream;
        char next_char;

        if (!stream)
        {
            t.state = false;
            return t;
        }

        //discard spaces
        do
        {
            stream >> next_char;
        } while (std::isspace((unsigned char) next_char));

        if (!stream)
        {
            t.state = false;
            return t;
        }

        stream.unget();

        if (std::isalpha((unsigned char) next_char) || next_char == '_')
        {
            tk = t.read_identifier();
        }
        else if (std::isdigit((unsigned char) next_char))
        {
            tk = t.read_number();
        }
        else if (t.is_operator(next_char))
        {
            tk = t.read_operator();
        }
        else
        {
            throw std::invalid_argument("character outside of character set encountered");
        }

        return t;
    }

    tokenizer::tokenizer_iterator::tokenizer_iterator():
            tknizer(nullptr)
    {}

    tokenizer::tokenizer_iterator::tokenizer_iterator(tokenizer& tkzer):
            tknizer(&tkzer)
    {
        *tknizer >> tk;
    }

    tokenizer::tokenizer_iterator& tokenizer::tokenizer_iterator::operator++()
    {
        *tknizer >> tk;
        return *this;
    }

    tokenizer::tokenizer_iterator tokenizer::tokenizer_iterator::operator++(int)
    {
        auto copy = *this;
        ++*this;
        return copy;
    }

    token& tokenizer::tokenizer_iterator::operator*()
    {
        return tk;
    }

    bool operator!=(const tokenizer_iterator& lhs, const tokenizer_iterator& rhs)
    {
        return lhs.tknizer == rhs.tknizer;
    }
}
