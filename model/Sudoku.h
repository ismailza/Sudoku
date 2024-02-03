#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

using namespace std;

class Sudoku
{
private:
    int size;
    int boxSize;
    int difficulty;
    vector<vector<unsigned int>> board;

    bool findUnassignedLocation(int &, int &);
    bool solveSudoku(int, int, vector<unsigned int>);
    vector<unsigned int> generateRandomPermutation(int);

public:
    Sudoku(int, int);
    int getSize();
    void setSize(int);
    int getDifficulty();
    int getBoxSize();
    void initBoard();
    Sudoku &operator=(const Sudoku &);
    void printBoard();
    bool solveSudoku();
    bool checkValue(int, int, unsigned int);
    unsigned int getValueAt(int, int);
    void setValueAt(int, int, unsigned int);
    vector<vector<unsigned int>> getBoard();
    void resetBoard();
    bool isSolved();
    bool isSolvable();
};

#endif // SUDOKU_H
