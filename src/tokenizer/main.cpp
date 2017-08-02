#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "tokenizer.hpp"

std::ostream& operator<<(std::ostream& os, const std::vector<token>& tokens)
{
	std::string initial_expr;
	for (const token& t : tokens)
	{
		std::string type_str;
		switch (t.tp)
		{
		case token::token_type::NAME:
			type_str = "name";
			break;
		case token::token_type::NUMBER:
			type_str = "number";
			break;
		case token::token_type::OP:
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

int main()
{
	std::istringstream ss("a = b + 5");
	std::cout << ss.str() << '\n';
	tokenizer t(ss);
	std::vector<token> tokens(5);
	for (auto& tk : tokens)
	{
		t >> tk;
	}

	std::vector<token> correct_answer{
		token{token::token_type::NAME, "a"},
		token{token::token_type::OP, "="},
		token{token::token_type::NAME, "b"},
		token{token::token_type::OP, "+"},
		token{token::token_type::NUMBER, "5"}
	};
	std::cout << tokens;

	if (tokens.size() != correct_answer.size() || !std::equal(tokens.begin(), tokens.end(), correct_answer.begin()))
	{
		throw std::logic_error("tokenizer doesn't work");
	}


}