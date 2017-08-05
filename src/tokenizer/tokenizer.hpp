#ifndef COMPILER_TOKENIZER_HPP
#define COMPILER_TOKENIZER_HPP

#include <iostream>
#include <iterator>

#include "token.hpp"

namespace markargs
{
    class tokenizer
    {
        std::istream* stream;
        bool state;
    public:
        class tokenizer_iterator
        {
            token tk;
            tokenizer* tknizer;
        public:
            using iterator_category = std::input_iterator_tag;
            using value_type = token;
            using reference = value_type&;
            using pointer = value_type*;
            using difference_type = void; //doesn't make much sense

            tokenizer_iterator();

            explicit tokenizer_iterator(tokenizer& tkzer);

            token& operator*();

            tokenizer_iterator& operator++();
            tokenizer_iterator operator++(int);

            friend bool operator!=(const tokenizer_iterator& lhs,
                                   const tokenizer_iterator& rhs);
        };

        explicit tokenizer(std::istream& is) noexcept;

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

    using tokenizer_iterator = tokenizer::tokenizer_iterator;
}

#endif
