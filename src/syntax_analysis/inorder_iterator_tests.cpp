#include <sstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>

#include <token.hpp>
#include "syntax_tree.hpp"

void test_one(const std::string& inputline, const std::string& correct_answer)
{
    std::stringstream ss(inputline);
    markargs::syntax_tree tree{std::istream_iterator<markargs::token>(ss), {}};
    std::ostringstream result;

    auto begin = tree.inorder_begin();
    auto end = tree.inorder_end();

    for (; begin != end; ++begin)
    {
        result << begin->payload();
    }

    if (result.str() != correct_answer)
    {
        std::cout << result.str() << '\n';
        throw std::logic_error{"tree was not build correctly for input: "
                               + inputline};
    }
}

void run_tests()
{
    std::ifstream input_file("input.txt");
    std::ifstream answers_file("answers.txt");
    if (!input_file.is_open() || !answers_file.is_open())
    {
        throw std::runtime_error{"either input or answers file cannot be opened"};
    }

    std::string inputline;
    std::string correct_answer;

    std::cout << "starting inorder iterator tests ...\n";
    unsigned int counter = 1;
    while (std::getline(input_file, inputline) && std::getline(answers_file, correct_answer))
    {
        std::cout << "running test #" << counter << '\n';
        test_one(inputline, correct_answer);
        ++counter;
    }

    std::cout << "all tests passed\n\n";
}

int main()
{
    run_tests();
}

