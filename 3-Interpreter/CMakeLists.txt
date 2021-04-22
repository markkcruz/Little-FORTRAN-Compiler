cmake_minimum_required(VERSION 3.17)
project(3_Interpreter)

set(CMAKE_CXX_STANDARD 11)

add_executable(3_Interpreter prog3.cpp lex.cpp val.cpp parserInt.cpp parserInt.cpp)