#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <map>
#include <stack>
#include <queue>
#include <sstream>

#include <token.hpp>
#include "syntax_tree.hpp"

void test_one(const std::string& inputline, const std::string& correct_answer)
{
    std::stringstream ss(inputline);
    markargs::syntax_tree tree{std::istream_iterator<markargs::token>(ss), {}};
    std::stringstream result;
    result << tree;
    if (result.str() != correct_answer)
    {
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

    std::cout << "starting simple tests ...\n";
    unsigned int counter = 1;
    while (std::getline(input_file, inputline) && std::getline(answers_file, correct_answer))
    {
        std::cout << "running test #" << counter << '\n';
        test_one(inputline, correct_answer);
        ++counter;
    }

    std::cout << "all tests passed\n\n";
}

void run_throwing_tests()
{
    std::ifstream input_file("failing_input.txt");
    if (!input_file.is_open())
    {
        throw std::runtime_error{"failing_input.txt cannot be opened"};
    }

    unsigned int counter = 1;
    std::cout << "starting throwing tests ...\n";
    std::string input_line;
    while (std::getline(input_file, input_line))
    {
        std::cout << "running test #" << counter << '\n';
        try
        {
            //correct answer can be anything,
            //since it should throw anyway
            test_one(input_line, "");
        }
        catch(std::invalid_argument& err)
        {
            ++counter;
            continue;
        }
        throw std::logic_error{"tree didn't throw on incorrect input"};
    }
    std::cout << "all tests passed\n\n";
}

int main()
{
    using namespace markargs;

    run_tests();
    run_throwing_tests();
}
