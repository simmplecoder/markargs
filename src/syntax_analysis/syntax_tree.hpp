#ifndef COMPILER_PARSE_TREE_HPP
#define COMPILER_PARSE_TREE_HPP

#include <string>
#include <queue>
#include <map>
#include <iosfwd>
#include <stack>

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
        class inorder_iterator : public std::iterator<std::forward_iterator_tag, token>
        {
            friend syntax_tree;

            node* current_node;
            std::stack<node*> prev_nodes;
            //std::stack<node*> visited_nodes;
            std::map<node*, bool> visited;
        public:
            inorder_iterator();

            inorder_iterator& operator++();
            inorder_iterator operator++(int);

            token& operator*();
            const token& operator*() const;

            token* operator->();
            const token* operator->() const;

            friend bool operator==(const inorder_iterator& lhs, const inorder_iterator& rhs);
            friend bool operator!=(const inorder_iterator& lhs, const inorder_iterator& rhs);

        private:
            inorder_iterator(node* current);
            node* find_leftmost_node(node* from);
        };

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

        syntax_tree(const syntax_tree& other) = delete;
        syntax_tree& operator=(const syntax_tree& other) = delete;

        syntax_tree(syntax_tree&& other) noexcept;
        syntax_tree& operator=(syntax_tree&& other) = delete;

        inorder_iterator inorder_begin();
        inorder_iterator inorder_end();

        ~syntax_tree();

        friend std::ostream& operator<<(std::ostream& os, syntax_tree& tree);
    private:
        void parse(std::queue<token>& tokens);
        void recursive_destruct(node* n);

        void sweep_until_lowerprec(std::stack<node*, std::vector<node*>>& prev_expressions,
                                   std::stack<token, std::vector<token>>& operator_tokens,
                                   const token& current_token);
        void sweep_all(std::stack<node*, std::vector<node*>>& prev_expressions,
                       std::stack<token, std::vector<token>>& operator_tokens);
    };
}

#endif //COMPILER_PARSE_TREE_HPP
