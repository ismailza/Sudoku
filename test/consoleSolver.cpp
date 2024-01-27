#include <iostream>
#include <chrono>

#include "../model/Sudoku.cpp"

using namespace chrono;

int main() {
  high_resolution_clock::time_point start, end;
  int difficulty, size;
  do {
    cout << "Enter difficulty (0 - Easy, 1 - Medium, 2 - Hard): ";
    cin >> difficulty;
  } while (difficulty < 0 || difficulty > 2);
  do {
    cout << "Enter size (4 - 4x4, 9 - 9x9, 16 - 16x16): ";
    cin >> size;
  } while (size != 4 && size != 9 && size != 16);

  Sudoku s(difficulty, size);
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