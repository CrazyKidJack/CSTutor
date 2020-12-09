#include "../Headers/Puzzle.hpp"
using namespace std;
using namespace jSoft::Sudoku;

Puzzle::Puzzle(){
  /*
  for (short rowIdx = 0; rowIdx < Puzzle::DIMENSION; ++rowIdx)
    for (short colIdx = 0; colIdx < Puzzle::DIMENSION; ++colIdx)
      grid_[rowIdx][colIdx] = 0;
  */
}//end default constructor

short (&Puzzle::grid())[9][9]{
  return grid_;
}//end grid()