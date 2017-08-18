#include "syntax_tree.hpp"

namespace markargs
{
    syntax_tree::inorder_iterator::inorder_iterator(node* current) :
            current_node(current)
    {
        current_node = find_leftmost_node(current);
        visited[current_node] = true;
    }

    syntax_tree::node* syntax_tree::inorder_iterator::find_leftmost_node(node* from)
    {
        if (from->left_operand != nullptr)
        {
            prev_nodes.push(from);
            return find_leftmost_node(from->left_operand);
        }

        return from;
    }

    syntax_tree::inorder_iterator::inorder_iterator() :
            current_node(nullptr)
    {}

    syntax_tree::inorder_iterator& syntax_tree::inorder_iterator::operator++()
    {
        if (current_node->left_operand != nullptr && !visited[current_node->left_operand])
        {
            prev_nodes.push(current_node);
            current_node = current_node->left_operand;
            return ++*this; //recurse
        }

        if (!visited[current_node])
        {
            visited[current_node] = true;
            return *this;
        }
        else
        {
            //prev_nodes.pop();
            if (current_node->right_operand != nullptr)
            {
                current_node = current_node->right_operand;
                return ++*this;
            }
            else
            {
                if (!prev_nodes.empty())
                {
                    current_node = prev_nodes.top();
                    prev_nodes.pop();
                    return ++*this;
                }
                else
                {
                    current_node = nullptr;
                    return *this;
                }
            }
        }
    }

    syntax_tree::inorder_iterator syntax_tree::inorder_iterator::operator++(int)
    {
        auto copy = *this;
        ++*this;
        return copy;
    }

    const token& syntax_tree::inorder_iterator::operator*() const
    {
        return current_node->tk;
    }

    token& syntax_tree::inorder_iterator::operator*()
    {
        return current_node->tk;
    }

    const token* syntax_tree::inorder_iterator::operator->() const
    {
        return &current_node->tk;
    }

    token* syntax_tree::inorder_iterator::operator->()
    {
        return &current_node->tk;
    }



    bool operator==(const syntax_tree::inorder_iterator lhs, const syntax_tree::inorder_iterator rhs)
    {
        return lhs.current_node == rhs.current_node;
    }

    bool operator!=(const syntax_tree::inorder_iterator lhs, const syntax_tree::inorder_iterator rhs)
    {
        return !(lhs == rhs);
    }
}