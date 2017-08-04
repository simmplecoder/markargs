cmake_minimum_required(VERSION 3.2)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(tokenizer
        main.cpp
        tokenizer.hpp
        token.hpp
        syntax_error.hpp
        tokenizer.cpp)
