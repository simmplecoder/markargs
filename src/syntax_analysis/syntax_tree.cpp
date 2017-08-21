#include "syntax_tree.hpp"
#include <utility>
#include <stack>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iterator>

namespace markargs
{

    syntax_tree::node::node(const markargs::token& tk_, node* left_operand_, node* right_operand_):
            tk(tk_),
            left_operand(left_operand_),
            right_operand(right_operand_)
    {}

    syntax_tree::syntax_tree(syntax_tree&& other) noexcept:
            root(other.root)
    {
        other.root = nullptr;
        std::swap(operator_precedence, other.operator_precedence);
    }

    void syntax_tree::parse(std::queue<markargs::token>& tokens)
    {
        std::stack<node*, std::vector<node*>> prev_expressions;
        std::stack<token, std::vector<token>> operator_tokens;

        constexpr auto name = token::token_type::NAME;
        constexpr auto op = token::token_type::OP;
        constexpr auto number = token::token_type::NUMBER;

        while (!tokens.empty())
        {
            const auto& current_token = tokens.front();

            switch (current_token.type())
            {
                case op:
                    sweep_until_lowerprec(prev_expressions, operator_tokens, current_token);
                    operator_tokens.push(current_token);
                    break;
                case number:
                    prev_expressions.push(new node{current_token});
                    break;
                case name:
                    prev_expressions.push(new node{current_token});
                    break;
                default:
                    throw std::invalid_argument{"unknown token type encountered"};
            }
            tokens.pop();
        }

        //if there are any tokens left, they are in the right order, e.g. expression
        //can be evaluated applying operators from right to left
        sweep_all(prev_expressions, operator_tokens);

        if (prev_expressions.size() != 1)
        {
            throw std::invalid_argument("erroneous number of operands encountered");
        }

        root = prev_expressions.top();
    }

    syntax_tree::inorder_iterator syntax_tree::inorder_begin()
    {
        return inorder_iterator{root};
    }

    syntax_tree::inorder_iterator syntax_tree::inorder_end()
    {
        return {};
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



    void syntax_tree::sweep_until_lowerprec(std::stack<node*, std::vector<node*>>& prev_expressions,
                                            std::stack<token, std::vector<token>>& operator_tokens,
                                            const token& current_token)
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
    }

    void syntax_tree::sweep_all(std::stack<node*, std::vector<node*>>& prev_expressions,
                                std::stack<token, std::vector<token>>& operator_tokens)
    {
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
    }

    std::ostream& operator<<(std::ostream& os, syntax_tree& tree)
    {
        std::transform(tree.inorder_begin(), tree.inorder_end(),
                       std::ostream_iterator<std::string>(os),
                       [](const token& tk){
                           return tk.payload();
                       });
    }
}