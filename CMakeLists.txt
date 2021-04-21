cmake_minimum_required(VERSION 3.10)
project(AP_Ex2)

set(CMAKE_CXX_STANDARD 20)

add_executable(AP_Ex2 main.cpp scanner.cpp scanner.h token.cpp token.h symtab.cpp symtab.h tokenstrings.h tokentype.h)