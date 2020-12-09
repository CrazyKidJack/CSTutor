#include <iostream>
#include <string>
#include "jSoft/Sudoku/Headers/Puzzle.hpp"

using namespace std;
using namespace jSoft::Sudoku;

int main(){
  Puzzle puzzle;

  for (short rowIdx = 0; rowIdx < Puzzle::DIMENSION; ++rowIdx){
    for (short colIdx = 0; colIdx < Puzzle::DIMENSION; ++colIdx){
      if(colIdx != 0) cout << "\t";

      cout << (puzzle.grid())[rowIdx][colIdx];
    }
    cout << endl;
  }
  
}//end main