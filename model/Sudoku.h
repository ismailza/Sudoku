#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>

using namespace std;

class Sudoku
{
private:
    int size;
    int boxSize;
    vector<vector<unsigned int>> board;

    bool checkValue(int, int, unsigned int);
    bool findUnassignedLocation(int &, int &);
    bool solveSudoku(int, int, vector<unsigned int>);
    vector<unsigned int> generateRandomPermutation(int);

public:
    Sudoku(int size);
    int getSize();
    void setSize(int size);
    int getBoxSize();
    void initBoard(const int);
    Sudoku &operator=(const Sudoku &);
    void printBoard();
    bool solveSudoku();
    unsigned int getBoardValue(int, int);
    void resetBoard();
};

#endif // SUDOKU_H
