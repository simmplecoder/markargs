cmake_minimum_required(VERSION 3.2)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_library(lexical_analysis token.hpp token.cpp)
set(LEXICAL_ANALYSIS_HEADER_FILES token.hpp)

add_executable(lexical_analysis_tests main.cpp)
target_link_libraries(lexical_analysis_tests lexical_analysis)
