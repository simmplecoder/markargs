#ifndef COMPILER_PARSE_TREE_HPP
#define COMPILER_PARSE_TREE_HPP

#include <string>
#include <queue>
#include <map>
#include <iosfwd>

#include <token.hpp>

namespace markargs
{
    class syntax_tree
    {
        struct node
        {
            markargs::token tk;
            node* left_operand;
            node* right_operand;

            explicit node(const markargs::token& tk_,
                          node* left_operand_ = nullptr,
                          node* right_operand_ = nullptr);
        };

        node* root;

        std::map<std::string, int> operator_precedence;
    public:
        template <typename InputIterator>
        syntax_tree(InputIterator first, InputIterator last):
                root(nullptr),
                operator_precedence
                        {
                {"=", 0},
                {"+", 1},
                {"-", 1}
                        }
        {
            std::queue<token> tokens{std::deque<token>{first, last}};
            parse(tokens);
        }

        friend std::ostream& operator<<(std::ostream& os, const syntax_tree& tree);
    private:
        void parse(std::queue<token>& tokens);
        void print(std::ostream& os, const node& n) const;
    };
}

#endif //COMPILER_PARSE_TREE_HPP
