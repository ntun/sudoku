cmake_minimum_required(VERSION 3.12)
project(sudoku)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sudoku
        main.cpp
        README.md
        Sudoku.cpp
        Sudoku.h)
