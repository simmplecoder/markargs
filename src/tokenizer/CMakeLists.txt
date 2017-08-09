cmake_minimum_required(VERSION 3.2)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_library(tokenizer tokenizer.cpp)
set(TOKENIZER_HEADER_FILES token.hpp tokenizer.hpp)

add_executable(tokenizer_tests
        main.cpp
        tokenizer.hpp
        token.hpp
        token.cpp
        tokenizer.cpp)
