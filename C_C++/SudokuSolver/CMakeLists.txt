cmake_minimum_required(VERSION 3.9)
project(SudokuSolver CXX)

add_executable(${PROJECT_NAME} solver.cpp jSoft/Sudoku/Sources/Puzzle.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
