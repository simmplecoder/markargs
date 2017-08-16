cmake_minimum_required(VERSION 3.2)
project(compiler)

set(CMAKE_CXX_STANDARD 14)

add_library(syntax_analysis syntax_tree.hpp syntax_tree.cpp)
target_include_directories(syntax_analysis PUBLIC ../lexical_analysis/)
target_link_libraries(syntax_analysis lexical_analysis)

add_executable(syntax_analysis_tests
        main.cpp
        syntax_tree.hpp
        )
target_link_libraries(syntax_analysis_tests lexical_analysis syntax_analysis)
target_include_directories(syntax_analysis_tests PUBLIC ../lexical_analysis/)

configure_file(./input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(./input.txt ${CMAKE_CURRENT_BINARY_DIR}/answers.txt COPYONLY)
configure_file(./failing_input.txt ${CMAKE_CURRENT_BINARY_DIR}/failing_input.txt COPYONLY)

add_test(syntax-analysis-tests syntax_analysis_tests)