#ifndef COMPILER_TOKENIZER_HPP
#define COMPILER_TOKENIZER_HPP

#include <iostream>

#include "syntax_error.hpp"
#include "token.hpp"

namespace markargs
{
    class tokenizer
    {
        std::istream* stream;
        bool state;
    public:
        tokenizer(std::istream& is) noexcept;

        //simultaneous access to multiple tokenizers
        //will have *very* surprising behavior
        tokenizer(const tokenizer& other) = delete;

        tokenizer& operator=(const tokenizer& other) = delete;

        tokenizer(tokenizer&& other) noexcept;

        tokenizer& operator=(tokenizer&& other) = delete;

        operator bool();

        friend tokenizer& operator>>(tokenizer&, token& tk);

    private:
        token read_identifier();

        token read_number();

        token read_operator();

        bool is_operator(char c) const noexcept;
    };
}

#endif
