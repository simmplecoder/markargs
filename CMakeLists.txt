cmake_minimum_required(VERSION 3.2)
project(compiler)
enable_testing()

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src/lexical_analysis)
add_subdirectory(src/syntax_analysis)
