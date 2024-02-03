#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>

#include "Sudoku.h"

/**
 * @brief Construct a new Sudoku with a given size
 * @param size The size of the Sudoku
 * @details The boxSize is calculated as the square root of the size and the board is initialized with 0
*/
Sudoku::Sudoku(int difficulty,int size) : difficulty(difficulty), size(size), boxSize((int)sqrt(size))
{
  board = vector<vector<unsigned int>>(size, vector<unsigned int>(size));
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      board[i][j] = 0;
  initBoard();
}

/**
 * @brief Set the size of the Sudoku
 * @param size The size of the Sudoku
 * @details The boxSize is calculated as the square root of the size
 * @return void
*/
void Sudoku::setSize(int size)
{
  this->size = size;
  this->boxSize = (int)sqrt(size);
}

/**
 * @brief Get the size of the Sudoku
 * @return The size of the Sudoku
*/
int Sudoku::getSize()
{
  return size;
}

/**
 * @brief Get the size of one box of the Sudoku
 * @return The size of one box of the Sudoku
*/
int Sudoku::getBoxSize()
{
  return boxSize;
}

/**
 * @brief Get the difficulty of the Sudoku
 * @return The difficulty of the Sudoku
*/
int Sudoku::getDifficulty()
{
  return difficulty;
}

/**
 * @brief Reset the board to 0
 * @return void
*/
void Sudoku::resetBoard()
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      board[i][j] = 0;
}

/**
 * @brief Copy the board of a Sudoku to another
 * @param s The Sudoku to copy
 * @return The Sudoku with the copied board
*/
Sudoku &Sudoku::operator=(const Sudoku &s)
{
  board.clear();
  this->size = s.size;
  this->boxSize = s.boxSize;
  this->difficulty = s.difficulty;
  board = vector<vector<unsigned int>>(size, vector<unsigned int>(size));
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      board[i][j] = s.board[i][j];
  return *this;
}

/**
 * @brief Initialize the board of the Sudoku with a given difficulty
 * @details First, the Sudoku is solved. Then, a number of cells are removed from the board
 * according to the difficulty.
 * @return void
*/
void Sudoku::initBoard()
{
  int rate, nb, row, col, i = 0;
  unsigned char value;
  switch (difficulty)
  {
  case 0:
    rate = 60; break;
  case 1:
    rate = 70; break;
  case 2:
    rate = 80; break;
  default:
    rate = 0;
  }
  
  solveSudoku();

  nb = static_cast<int>(pow(size, 2) * rate / 100);
  srand((unsigned int)time(nullptr));
  while (i < nb)
  {
    row = rand() % size;
    col = rand() % size;
    if (!board[row][col])
      continue;
    
    board[row][col] = 0;
    i++;
  }
}

/**
 * @brief Get the value of a cell
 * @param row The row of the cell
 * @param col The column of the cell
 * @return The value of the cell
*/
unsigned int Sudoku::getValueAt(int row, int col)
{
  return board[row][col];
}

/**
 * @brief Set the value of a cell
 * @param row The row of the cell
 * @param col The column of the cell
 * @param value The value to set
 * @return void
*/
void Sudoku::setValueAt(int row, int col, unsigned int value)
{
  board[row][col] = value;
}

/**
 * @brief Get the board of the Sudoku
 * @return The board of the Sudoku
*/
vector<vector<unsigned int>> Sudoku::getBoard()
{
  return board;
}

/**
 * @brief Solve the Sudoku
 * @param row The row of the cell
 * @param col The column of the cell
 * @param values The values to try in the cell
 * @return true if the Sudoku is solved, false otherwise
 * @details The algorithm is a backtracking algorithm, it tries to put a value in a 
 * cell and if it is not possible, it tries another value. If it is not possible to
 * put a value in a cell, it goes back to the previous cell and tries another value.
 * If it is not possible to put a value in the first cell, the Sudoku is not solvable.
*/
bool Sudoku::solveSudoku(int row, int col, vector<unsigned int> values)
{
  if (!findUnassignedLocation(row, col))
    return true;

  // vector<unsigned int> values = generateRandomPermutation(size);
  for (int value : values)
  {
    if (checkValue(row, col, value))
    {
      board[row][col] = value;
      if (solveSudoku(row, col, values))
        return true;
      board[row][col] = 0;
    }
  }

  // for (int i = 1; i <= size; i++)
  // {
  //   if (checkValue(row, col, i))
  //   {
  //     board[row][col] = i;
  //     if (solveSudoku(row, col))
  //       return true;
  //     board[row][col] = 0;
  //   }
  // }

  return false;
}

/**
 * @brief Solve the Sudoku
 * @return true if the Sudoku is solved, false otherwise
*/
bool Sudoku::solveSudoku()
{
  vector<unsigned int> values = generateRandomPermutation(size);
  return this->solveSudoku(0, 0, values);
}

/**
 * @brief Check if a value can be put in a cell
 * @param row The row of the cell
 * @param col The column of the cell
 * @param value The value to check
 * @return true if the value can be put in the cell, false otherwise
 * @details The value is checked in the row, the column and the square of the cell
*/
bool Sudoku::checkValue(int row, int col, unsigned int value)
{
  // Check row and column
  for (int i = 0; i < size; i++)
  {
    if (i != col && board[row][i] == value)
      return false;
    if (i != row && board[i][col] == value)
      return false;
  }

  // Check square
  int rowStart = (row / boxSize) * boxSize;
  int colStart = (col / boxSize) * boxSize;
  int rowEnd = rowStart + boxSize;
  int colEnd = colStart + boxSize;
  for (int i = rowStart; i < rowEnd; i++) {
    if (i != row) {
      for (int j = colStart; j < colEnd; j++)
        if (j != col && board[i][j] == value)
          return false;
    }
  }

  return true;
}

/**
 * @brief Generate a random permutation of values between 1 and maxValue.
 * @param maxValue maximum value of generated permutation
 * @return generated permutation
 * @details This function generates a permutation of unique integers from 1 up to the specified 
 * maxValue. It first creates a sequence of numbers in ascending order and then shuffles this sequence 
 * to produce a random permutation. The function employs a Mersenne Twister engine (mt19937) for 
 * random shuffling, which is known for its high-quality pseudo-random number generation.
*/
vector<unsigned int> Sudoku::generateRandomPermutation(int maxValue)
{
  random_device m_rd;
  mt19937 m_mt{m_rd()};
	vector<unsigned int> values(maxValue);
	int n = 0;
	generate(values.begin(), values.end(), [&n]() { return ++n; });
	shuffle(values.begin(), values.end(), m_rd);
	return values;
}

/**
 * @brief Find an unassigned cell
 * @param row The row of the cell
 * @param col The column of the cell
 * @return true if an unassigned cell is found, false otherwise
 * @details The function returns true if an unassigned cell is found and false otherwise.
 * If an unassigned cell is found, the row and the column of the cell are updated.
*/
bool Sudoku::findUnassignedLocation(int &row, int &col)
{
  for (row = 0; row < size; row++)
    for (col = 0; col < size; col++)
      if (!board[row][col])
        return true;
  return false;
}

/**
 * @brief Print the board of the Sudoku
 * @return void
*/
void Sudoku::printBoard()
{
  for (int i = 0; i < size; i++)
  {
    if ((i % boxSize == 0) && (i != 0) && (i != size - 1))
      cout << endl;
    for (int j = 0; j < size; j++)
    {
      if ((j % boxSize == 0) && (j != 0) && (j != size - 1))
        cout << "\t";
      cout << (int)board[i][j] << " ";
    }
    cout << endl;
  }
}

/**
 * @brief Check if the Sudoku is solved
 * @return true if the Sudoku is solved, false otherwise
*/
bool Sudoku::isSolved()
{
  int row, col;
  return !findUnassignedLocation(row, col);
}

/**
 * @brief Check if the Sudoku is solvable
 * @return true if the Sudoku is solvable, false otherwise
*/
bool Sudoku::isSolvable()
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      if (board[i][j] != 0 && !checkValue(i, j, board[i][j]))
        return false;
  return true;
}