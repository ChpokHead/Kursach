cmake_minimum_required(VERSION 3.15)
project(Kursach)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled3 main.cpp LexAnalyser.cpp SyntaxAnalyser.cpp SyntaxAnalyser.h Token.cpp Token.h Enums.h IDTable.h IDTable.cpp)