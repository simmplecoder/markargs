#include "syntax_tree.hpp"
#include <utility>
#include <stack>
#include <string>
#include <stdexcept>

namespace markargs
{

    syntax_tree::node::node(const markargs::token& tk_, node* left_operand_, node* right_operand_):
            tk(tk_),
            left_operand(left_operand_),
            right_operand(right_operand_)
    {}

    void syntax_tree::parse(std::queue<markargs::token>& tokens)
    {
        std::stack<node*, std::vector<node*>> prev_expressions;
        std::stack<token, std::vector<token>> operator_tokens;

        if (tokens.front().type() != token::token_type::NAME)
        {
            throw std::invalid_argument{"name must be first in the expression"};
        }


        prev_expressions.push(new node{tokens.front()});
        tokens.pop();

        constexpr auto name = token::token_type::NAME;
        constexpr auto op = token::token_type::OP;
        constexpr auto number = token::token_type::NUMBER;

        while (!tokens.empty())
        {
            const auto& current_token = tokens.front();

            if (current_token.type() == op)
            {

                while (!operator_tokens.empty() &&
                       operator_precedence[operator_tokens.top().payload()] >=
                       operator_precedence[current_token.payload()])
                {
                    auto oper = operator_tokens.top();
                    operator_tokens.pop();

                    if (prev_expressions.size() < 2)
                    {
                        throw std::invalid_argument{"either or both left or right side operands are missing"};
                    }

                    auto right_operand = prev_expressions.top();
                    prev_expressions.pop();
                    auto left_operand = prev_expressions.top();
                    prev_expressions.pop();

                    prev_expressions.push(new node{oper, left_operand, right_operand});
                }

                operator_tokens.push(current_token);
            }
            else if (current_token.type() == number)
            {
                prev_expressions.push(new node{current_token});
            }
            else if (current_token.type() == name)
            {
                prev_expressions.push(new node{current_token});
            }
            else
            {
                throw std::invalid_argument{"unknown token type encountered"};
            }

            tokens.pop();
        }

        //if there are any tokens left, they are in the right order, e.g. expression
        //can be evaluated applying operators from right to left
        while (!operator_tokens.empty())
        {
            auto oper = operator_tokens.top();
            operator_tokens.pop();

            if (prev_expressions.size() < 2)
            {
                throw std::invalid_argument{"either or both left or right side operands are missing"};
            }

            auto right_operand = prev_expressions.top();
            prev_expressions.pop();
            auto left_operand = prev_expressions.top();
            prev_expressions.pop();

            prev_expressions.push(new node{oper, left_operand, right_operand});
        }

        if (prev_expressions.size() != 1)
        {
            throw std::invalid_argument("erroneous number of operands encountered");
        }

        root = prev_expressions.top();
    }

    void syntax_tree::print(std::ostream& os, const node& n) const
    {
        const node* current = &n;
        if (current->left_operand != nullptr)
        {
            print(os,*(current->left_operand));
        }

        os << current->tk.payload();

        if (current->right_operand != nullptr)
        {
            print(os, *(current->right_operand));
        }
    }

    void syntax_tree::recursive_destruct(node* n)
    {
        if (n->left_operand != nullptr)
        {
            recursive_destruct(n->left_operand);
        }

        if (n->right_operand != nullptr)
        {
            recursive_destruct(n->right_operand);
        }

        delete n;
    }

    syntax_tree::~syntax_tree()
    {
        if (root != nullptr)
        {
            recursive_destruct(root);
        }
    }

    std::ostream& operator<<(std::ostream& os, const syntax_tree& tree)
    {
        tree.print(os, *tree.root);
    }
}