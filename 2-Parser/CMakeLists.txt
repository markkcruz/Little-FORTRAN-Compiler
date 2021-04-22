cmake_minimum_required(VERSION 3.17)
project(Program_Assignment_2_Parser_V2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Program_Assignment_2_Parser_V2 lex.cpp prog2.cpp parse.h lex.h parse.cpp)