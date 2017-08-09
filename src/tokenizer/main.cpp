//#include <iostream>
//#include <vector>
//#include <stdexcept>
//#include <sstream>
//#include <algorithm>
//
//#include "tokenizer.hpp"
//
//std::ostream& operator<<(std::ostream& os, const std::vector<markargs::token>& tokens)
//{
//	std::string initial_expr;
//	for (const markargs::token& t : tokens)
//	{
//		std::string type_str;
//		switch (t.current_tp)
//		{
//        case markargs::token::token_type::NAME:
//			type_str = "name";
//			break;
//        case markargs::token::token_type::NUMBER:
//			type_str = "number";
//			break;
//        case markargs::token::token_type::OP:
//			type_str = "operator";
//			break;
//		default:
//			throw std::logic_error("unknown token encountered");
//		}
//		os << "token type: " << type_str << '\n' 
//			<< "payload: " << t.payload << "\n--------------------\n";
//		initial_expr += t.payload;
//	}
//	std::cout << "initial expression: " << initial_expr << '\n';
//
//	return os;
//}
//
//void fixed_tokencount_check()
//{
//    std::istringstream ss("a = b + 5");
//    std::cout << ss.str() << '\n';
//    markargs::tokenizer tokenizer(ss);
//    std::vector<markargs::token> tokens(5);
//    for (auto& token : tokens)
//    {
//        tokenizer >> token;
//    }
//
//    std::vector<markargs::token> correct_answer{
//            markargs::token{markargs::token::token_type::NAME, "a"},
//            markargs::token{markargs::token::token_type::OP, "="},
//            markargs::token{markargs::token::token_type::NAME, "b"},
//            markargs::token{markargs::token::token_type::OP, "+"},
//            markargs::token{markargs::token::token_type::NUMBER, "5"}
//    };
//    std::cout << tokens;
//
//    if (tokens.size() != correct_answer.size() || !std::equal(tokens.begin(), tokens.end(), correct_answer.begin()))
//    {
//        throw std::logic_error("tokenizer doesn't work");
//    }
//}
//
//void read_tilend_check()
//{
//    std::string expr_str("a = b + 5");
//    std::istringstream ss1(expr_str);
//    std::istringstream ss2(expr_str);
//    std::cout << ss1.str() << '\n';
//    markargs::tokenizer tokenizer(ss1);
//    markargs::tokenizer tokenizer_copy(ss2);
//
//    //exhaust tokenizer
//    std::vector<markargs::token> tokenizer_result;
//    markargs::token tk;
//    while (tokenizer >> tk)
//    {
//        tokenizer_result.push_back(tk);
//    }
//
//    markargs::tokenizer_iterator first(tokenizer_copy);
//    markargs::tokenizer_iterator last;
//    std::vector<markargs::token> tokenizer_it_result{first, last};
//
//
//    std::vector<markargs::token> correct_answer{
//            markargs::token{markargs::token::token_type::NAME, "a"},
//            markargs::token{markargs::token::token_type::OP, "="},
//            markargs::token{markargs::token::token_type::NAME, "b"},
//            markargs::token{markargs::token::token_type::OP, "+"},
//            markargs::token{markargs::token::token_type::NUMBER, "5"}
//    };
//    std::cout << "tokenizer result:\n" << tokenizer_result << '\n';
//    std::cout << "tokenizer_iterator result:\n" << tokenizer_it_result << '\n';
//
//    if (tokenizer_result.size() != correct_answer.size() ||
//            !std::equal(tokenizer_result.begin(), tokenizer_result.end(), correct_answer.begin()))
//    {
//        throw std::logic_error("tokenizer doesn't work");
//    }
//
//    if (tokenizer_it_result.size() != correct_answer.size() ||
//        !std::equal(tokenizer_it_result.begin(), tokenizer_it_result.end(), correct_answer.begin()))
//    {
//        throw std::logic_error("tokenizer_iterator doesn't work");
//    }
//}
//
//int main()
//{
//    fixed_tokencount_check();
//    read_tilend_check();
//}

#include "token.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    static const struct {
        std::string input;
        std::vector<markargs::token> tokens;
        void operator()() const {
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
            { "foo = bar + 42", {
                                        {markargs::token::token_type::NAME, "foo"},
                                        {markargs::token::token_type::OP, "="},
                                        {markargs::token::token_type::NAME, "bar"},
                                        {markargs::token::token_type::OP, "+"},
                                        {markargs::token::token_type::NUMBER, "42"},
                                }},

            { "foo=bar+42       ", {
                                        {markargs::token::token_type::NAME, "foo"},
                                        {markargs::token::token_type::OP, "="},
                                        {markargs::token::token_type::NAME, "bar"},
                                        {markargs::token::token_type::OP, "+"},
                                        {markargs::token::token_type::NUMBER, "42"},
                                }},

            { "       _", {
                                        {markargs::token::token_type::NAME, "_"},
                                }},

            { "        ", {
                                }},

            { "ma = 35p42", {
                                        {markargs::token::token_type::NAME, "ma"},
                                        {markargs::token::token_type::OP, "="},
                                        {markargs::token::token_type::NUMBER, "35"},
                                        {markargs::token::token_type::NAME, "p42"},
                                }},

            { "+-_=", {
                                        {markargs::token::token_type::OP, "+"},
                                        {markargs::token::token_type::OP, "-"},
                                        {markargs::token::token_type::NAME, "_"},
                                        {markargs::token::token_type::OP, "="},
                                }},

    };

    for (const auto t : tests) {
        t();
    }
}
