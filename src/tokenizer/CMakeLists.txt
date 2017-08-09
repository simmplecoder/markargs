cmake_minimum_required(VERSION 3.2)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_library(tokenizer token.cpp)
set(TOKENIZER_HEADER_FILES token.hpp)

add_executable(tokenizer_tests
        main.cpp
        token.hpp
        token.cpp)
