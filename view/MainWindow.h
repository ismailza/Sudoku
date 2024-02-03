#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SFML/Graphics.hpp>

#include "../config/config.h"

#include "MenuButton.cpp"
#include "SudokuSquare.cpp"
#include "CircleNumberButton.cpp"
#include "../model/Sudoku.cpp"

class MainWindow
{
  private:
    int width;
    int height;
    int squareSize;
    Sudoku *sudoku;

    vector<vector<SudokuSquare *>> sudokuSquares;
    vector<MenuButton *> menuButtons;
    vector<vector<CircleNumberButton *>> numberButtons;
    SudokuSquare *clickedSquare;

    bool gamePaused;
    Time pauseStartTime; // Time when the game was paused
    Time totalPausedTime; // Total time paused
    bool gameFinished;
    bool animationFinished;
    int animationStage;

    
    Font font;
    Font headerFont;
    Text playerText;
    Text difficultyText;
    Text clockText;
    Clock *clock;
    Time pausedTime;

    void onMouseButtonClicked(const Vector2f &);
    void onMouseMoved(const Vector2f &);
    void onKeyButtonClicked(Event::TextEvent);
    void onBackspaceButtonClicked();
    void onNewGameButtonClicked();
    void onSolveButtonClicked();
    void onPauseButtonClicked();
    void updateClock();
    void update(int, int, int);
    void onAnimationStageChanged();

  public:
    MainWindow(int, int, const string &);
    ~MainWindow();
    void run();
};

#endif // MAINWINDOW_H