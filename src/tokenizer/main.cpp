#include "token.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    static const struct
    {
        std::string input;
        std::vector<markargs::token> tokens;

        void operator()() const
        {
            std::istringstream ss{input};
            std::vector<markargs::token> gen{
                    std::istream_iterator<markargs::token>(ss),
                    std::istream_iterator<markargs::token>()
            };
            std::cout << (gen == tokens ? "OK  " : "BAD ")
                      << "\"" << input << "\""
                      << "\n\twanted ";
            std::copy(tokens.begin(), tokens.end(),
                      std::ostream_iterator<markargs::token>(std::cout, ""));
            std::cout
                    << "\n\tgot    ";
            std::copy(gen.begin(), gen.end(),
                      std::ostream_iterator<markargs::token>(std::cout, ""));
            std::cout << '\n';
        }
    } tests[]{
            {"foo = bar + 42",    {
                                          {markargs::token::token_type::NAME, "foo"},
                                          {markargs::token::token_type::OP, "="},
                                          {markargs::token::token_type::NAME,   "bar"},
                                          {markargs::token::token_type::OP,   "+"},
                                          {markargs::token::token_type::NUMBER, "42"},
                                  }},

            {"foo=bar+42       ", {
                                          {markargs::token::token_type::NAME, "foo"},
                                          {markargs::token::token_type::OP, "="},
                                          {markargs::token::token_type::NAME,   "bar"},
                                          {markargs::token::token_type::OP,   "+"},
                                          {markargs::token::token_type::NUMBER, "42"},
                                  }},

            {"       _",          {
                                          {markargs::token::token_type::NAME, "_"},
                                  }},

            {"        ",          {
                                  }},

            {"ma = 35p42",        {
                                          {markargs::token::token_type::NAME, "ma"},
                                          {markargs::token::token_type::OP, "="},
                                          {markargs::token::token_type::NUMBER, "35"},
                                          {markargs::token::token_type::NAME, "p42"},
                                  }},

            {"+-_=",              {
                                          {markargs::token::token_type::OP,   "+"},
                                          {markargs::token::token_type::OP, "-"},
                                          {markargs::token::token_type::NAME,   "_"},
                                          {markargs::token::token_type::OP,   "="},
                                  }},

    };

    for (const auto& t : tests) {
        t();
    }
}
