#include <iostream>
#include <chrono>

#include "../model/Sudoku.cpp"

using namespace chrono;

int main() {
  high_resolution_clock::time_point start, end;
  Sudoku s(9);
  s.initBoard(1);
  s.printBoard();
  cout << "***********************************" << endl;
  start = high_resolution_clock::now();
  bool solved = s.solveSudoku();
  end = high_resolution_clock::now();

  cout << "Time taken: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;
  cout << "***********************************" << endl;
  if (solved)
    s.printBoard();
  else
    cout << "No solution exists" << endl;
  
  return 0;
}