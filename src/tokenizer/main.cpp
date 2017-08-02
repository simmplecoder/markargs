#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "tokenizer.hpp"

//struct token {
//	enum class type { NUMBER, NAME, OP };
//	type tp;
//	std::string payload;
//
//	token(type t, const std::string& payload_) :
//		tp(t),
//		payload(payload_)
//	{}
//};
//
//enum class analyzis_error {
//	NAME_FIRST_EXPECTED,
//	EQUALS_SECOND_EXPECTED,
//	NO_DOUBLE_EQUALS_EXPECTED,
//	CLOSING_VALUE_OR_NAME_EXPECTED
//};
//
//std::vector<token> tokenize(std::string_view s)
//{
//	std::vector<token> tokens;
//
//	std::string current_identifier;
//	std::string current_number;
//
//	for (char c : s)
//	{
//		if (std::isalpha((unsigned char)c) || c == '_')
//		{
//			if (!current_number.empty())
//			{
//				throw std::invalid_argument("any combination of consecutive numbers and names are not allowed");
//			}
//			current_identifier += c;
//		}
//		else if (std::isdigit((unsigned char)c))
//		{
//			if (!current_identifier.empty())
//			{
//				current_identifier += c;
//			}
//			else
//			{
//				current_number += c;
//			}
//		}
//		else if (c == '+' || c == '-' || c == '=')
//		{
//			if (!current_identifier.empty())
//			{
//				if (!tokens.empty() && (tokens.back().tp == token::type::NAME || tokens.back().tp == token::type::NUMBER))
//				{
//					throw std::invalid_argument("any combination of consecutive numbers and names are not allowed");
//				}
//				tokens.push_back(token{ token::type::NAME, current_identifier });
//				current_identifier.clear();
//			}
//			else if (!current_number.empty()) //they are not allowed to be simultaneously non-empty
//			{
//				if (!tokens.empty() && (tokens.back().tp == token::type::NAME || tokens.back().tp == token::type::NUMBER))
//				{
//					throw std::invalid_argument("any combination of consecutive numbers and names are not allowed");
//				}
//				tokens.push_back(token{ token::type::NUMBER, current_number });
//				current_number.clear();
//			}
//
//			if (!tokens.empty() && tokens.back().tp == token::type::OP)
//			{
//				throw std::invalid_argument("two consecutive operators are not allowed");
//			}
//			tokens.push_back(token{ token::type::OP, std::string(1, c) });
//		}
//		else if (std::isspace((unsigned char)c))
//		{
//			if (!current_identifier.empty())
//			{
//				if (!tokens.empty() && (tokens.back().tp == token::type::NAME || tokens.back().tp == token::type::NUMBER))
//				{
//					throw std::invalid_argument("any combination of consecutive numbers and names are not allowed");
//				}
//				tokens.push_back(token{ token::type::NAME, current_identifier });
//				current_identifier.clear();
//			}
//			else if (!current_number.empty()) //they are not allowed to be simultaneously non-empty
//			{
//				if (!tokens.empty() && (tokens.back().tp == token::type::NAME || tokens.back().tp == token::type::NUMBER))
//				{
//					throw std::invalid_argument("any combination of consecutive numbers and names are not allowed");
//				}
//				tokens.push_back(token{ token::type::NUMBER, current_number });
//				current_number.clear();
//			}
//		}
//		else
//		{
//			throw std::invalid_argument("character outside character set is encountered");
//		}
//	}
//
//	if (!current_identifier.empty())
//	{
//		tokens.push_back(token{ token::type::NAME, current_identifier });
//	}
//	else if (!current_number.empty())
//	{
//		tokens.push_back(token{ token::type::NUMBER, current_number });
//	}
//
//	return tokens;
//}
//
//std::pair<analyzis_error, bool> analyze(const std::vector<token> tokens)
//{
//	
//	auto it = tokens.begin();
//
//	if (it->tp != token::type::NAME)
//	{
//		return { analyzis_error::NAME_FIRST_EXPECTED, true };
//	}
//	++it;
//
//	//check for equals operator coming second in an expression
//	if (!(it->tp == token::type::OP && it->payload == "="))
//	{
//		return { analyzis_error::EQUALS_SECOND_EXPECTED, true};
//	}
//	++it;
//
//	for (auto i = ++it; i != tokens.end(); ++i)
//	{
//		if (i->tp == token::type::OP && i->payload == "=")
//		{
//			return { analyzis_error::NO_DOUBLE_EQUALS_EXPECTED, true };
//		}
//	}
//
//	if (tokens.back().tp == token::type::OP)
//	{
//		return { analyzis_error::CLOSING_VALUE_OR_NAME_EXPECTED, true };
//	}
//
//	return { {}, false };
//}
//
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
//
//std::ostream& operator<<(std::ostream& os, analyzis_error err)
//{
//	switch (err)
//	{
//	case analyzis_error::EQUALS_SECOND_EXPECTED:
//		os << "equals are expected as the second token in an expression";
//		break;
//	case analyzis_error::NAME_FIRST_EXPECTED:
//		os << "name is expected as the first token in an expression";
//		break;
//	case analyzis_error::NO_DOUBLE_EQUALS_EXPECTED:
//		os << "equals operator appeared twice or more, but not allowed to";
//		break;
//	case analyzis_error::CLOSING_VALUE_OR_NAME_EXPECTED:
//		os << "expression ended with an operator, which is noted allowed";
//		break;
//	default:
//		os << "unknown error";
//	}
//
//	return os;
//}

int main()
{
	//std::string expr;
	//std::getline(std::cin, expr);
	//std::vector<token> tokens;
	//try
	//{
	//	tokens = tokenize(expr);
	//}
	//catch (std::invalid_argument& err)
	//{
	//	std::cout << err.what() << '\n';
	//	return 0;
	//}
	//std::cout << tokens.size() << '\n';
	//std::cout << tokens;

	//auto analyzis_result = analyze(tokens);
	//if (analyzis_result.second)
	//{
	//	std::cout << analyzis_result.first << '\n';
	//}
	//else
	//{
	//	std::cout << "analyzis didn't find any errors\n";
	//}

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