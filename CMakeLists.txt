cmake_minimum_required(VERSION 3.2)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(tokenizer
        src/tokenizer/main.cpp
        src/tokenizer/tokenizer.hpp
        src/tokenizer/token.hpp
        src/tokenizer/syntax_error.hpp
        src/tokenizer/tokenizer.cpp)
add_subdirectory(src/tokenizer)
