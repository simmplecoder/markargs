#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "tokenizer.hpp"

std::ostream& operator<<(std::ostream& os, const std::vector<markargs::token>& tokens)
{
	std::string initial_expr;
	for (const markargs::token& t : tokens)
	{
		std::string type_str;
		switch (t.tp)
		{
        case markargs::token::token_type::NAME:
			type_str = "name";
			break;
        case markargs::token::token_type::NUMBER:
			type_str = "number";
			break;
        case markargs::token::token_type::OP:
			type_str = "operator";
			break;
		default:
			throw std::logic_error("unknown token encountered");
		}
		os << "token type: " << type_str << '\n' 
			<< "payload: " << t.payload << "\n--------------------\n";
		initial_expr += t.payload;
	}
	std::cout << "initial expression: " << initial_expr << '\n';

	return os;
}

void fixed_tokencount_check()
{
    std::istringstream ss("a = b + 5");
    std::cout << ss.str() << '\n';
    markargs::tokenizer tokenizer(ss);
    std::vector<markargs::token> tokens(5);
    for (auto& token : tokens)
    {
        tokenizer >> token;
    }

    std::vector<markargs::token> correct_answer{
            markargs::token{markargs::token::token_type::NAME, "a"},
            markargs::token{markargs::token::token_type::OP, "="},
            markargs::token{markargs::token::token_type::NAME, "b"},
            markargs::token{markargs::token::token_type::OP, "+"},
            markargs::token{markargs::token::token_type::NUMBER, "5"}
    };
    std::cout << tokens;

    if (tokens.size() != correct_answer.size() || !std::equal(tokens.begin(), tokens.end(), correct_answer.begin()))
    {
        throw std::logic_error("tokenizer doesn't work");
    }
}

void read_tilend_check()
{
    std::istringstream ss("a = b + 5");
    std::cout << ss.str() << '\n';
    markargs::tokenizer tokenizer(ss);
    std::vector<markargs::token> tokens;
    markargs::token tk;
    while (tokenizer >> tk)
    {
        tokens.push_back(tk);
    }

    std::vector<markargs::token> correct_answer{
            markargs::token{markargs::token::token_type::NAME, "a"},
            markargs::token{markargs::token::token_type::OP, "="},
            markargs::token{markargs::token::token_type::NAME, "b"},
            markargs::token{markargs::token::token_type::OP, "+"},
            markargs::token{markargs::token::token_type::NUMBER, "5"}
    };
    std::cout << tokens;

    if (tokens.size() != correct_answer.size() || !std::equal(tokens.begin(), tokens.end(), correct_answer.begin()))
    {
        throw std::logic_error("tokenizer doesn't work");
    }
}

int main()
{
    fixed_tokencount_check();
    read_tilend_check();
}