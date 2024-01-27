#include "MainWindow.h"

MainWindow::MainWindow(int difficulty, int size, const string &playerName)
{
  if (!headerFont.loadFromFile(FONT_PATH_DIR + string("Audiowide-Regular.ttf")))
    throw runtime_error("Couldn't load the font file 'Audiowide-Regular.ttf'. Check if the file exists in " + string(FONT_PATH_DIR) + " directory.");

  if (!font.loadFromFile(FONT_PATH_DIR + string("calibri.ttf")))
    throw runtime_error("Couldn't load the font file 'Roboto-Regular.ttf'. Check if the file exists in " + string(FONT_PATH_DIR) + " directory.");

  if (size <= 9)
    squareSize = 50;
  else
    squareSize = 30;

  int boardSize = squareSize * (size + 1);
  int headerHeight = 60;
  width = boardSize + 175;
  height = boardSize + headerHeight;

  sudoku = new Sudoku(difficulty, size);

  sudokuSquares.resize(size * size);
  clickedSquare = nullptr;
  gamePaused = false;
  gameFinished = false;
  animationFinished = false;
  animationStage = 0;
  clock = new Clock();

  playerText = Text(playerName, headerFont);
  playerText.setCharacterSize(18);
  playerText.setFillColor(Color::Black);
  playerText.setPosition(10, 5);

  difficultyText = Text(string(difficulty == 0 ? "Easy" : (difficulty == 1 ? "Medium" : "Hard")), headerFont);
  difficultyText.setCharacterSize(18);
  difficultyText.setFillColor(Color::Black);
  difficultyText.setPosition(width / 2 - 75, 5);

  clockText = Text("00:00", headerFont);
  clockText.setCharacterSize(18);
  clockText.setFillColor(Color::Black);
  clockText.setPosition(width - 90, 5);

  // Set up sudoku board
  sudokuSquares.resize(size);
  for (int i = 0; i < size; i++)
  {
    sudokuSquares[i].resize(size);
    for (int j = 0; j < size; j++)
    {
      int x = 5 + j * squareSize + (j / sudoku->getBoxSize()) * 2;
      int y = headerHeight + i * squareSize + (i / sudoku->getBoxSize()) * 2;
      sudokuSquares[i][j] = new SudokuSquare(i, j, x, y, squareSize, font, "");
      sudokuSquares[i][j]->setValue(sudoku->getValueAt(i, j));
      sudokuSquares[i][j]->setValueConstant(sudoku->getValueAt(i, j) != 0);
    }
  }

  // Set up menu buttons
  menuButtons.push_back(new MenuButton(width - 175, headerHeight + 40 * menuButtons.size(), 150, 40, font, "New Game", MenuButton::NEW_GAME));
  menuButtons.push_back(new MenuButton(width - 175, headerHeight + 40 * menuButtons.size(), 150, 40, font, "Pause", MenuButton::PAUSE_GAME));
  menuButtons.push_back(new MenuButton(width - 175, headerHeight + 40 * menuButtons.size(), 150, 40, font, "Solve", MenuButton::SOLVE_GAME));
}

MainWindow::~MainWindow()
{
  delete clock;
  for (auto &row : sudokuSquares)
    for (auto &square : row)
      delete square;
  for (auto &button : menuButtons)
    delete button;
}

void MainWindow::onMouseButtonClicked(const Vector2f &mousePosition)
{
  for (auto &button : menuButtons)
  {
    if (button->getGlobalBounds().contains(mousePosition))
    {
      switch (button->getFunction())
      {
      case MenuButton::NEW_GAME:
        onNewGameButtonClicked();
        break;
      case MenuButton::SOLVE_GAME:
        onSolveButtonClicked();
        break;
      case MenuButton::PAUSE_GAME:
        onPauseButtonClicked();
        break;
      default:
        break;
      }
      return;
    }
  }
  if (gameFinished)
    return;
  for (auto &row : sudokuSquares)
  {
    for (auto &square : row)
    {
      if (square->getGlobalBounds().contains(mousePosition))
      {
        if (clickedSquare != nullptr)
          clickedSquare->update(SudokuSquare::IDLE);
        clickedSquare = square;
        clickedSquare->update(SudokuSquare::CLICKED);
        update(clickedSquare->getRow(), clickedSquare->getCol(), clickedSquare->getValue());
        return;
      }
    }
  }
}

void MainWindow::onMouseMoved(const Vector2f &mousePosition)
{
  for (auto &button : menuButtons)
  {
    if (button->getGlobalBounds().contains(mousePosition))
      button->update(true);
    else
      button->update(false);
  }
}

void MainWindow::onKeyButtonClicked(Event::TextEvent text)
{
  if (gameFinished || clickedSquare == nullptr || clickedSquare->getValueConstant())
    return;
  if (text.unicode < '0' || '9' < text.unicode)
    return;

  unsigned int value = text.unicode - '0';
  update(clickedSquare->getRow(), clickedSquare->getCol(), value);
  sudoku->setValueAt(clickedSquare->getRow(), clickedSquare->getCol(), value);
}

void MainWindow::onBackspaceButtonClicked()
{
  if (!gameFinished && clickedSquare != nullptr && !clickedSquare->getValueConstant())
  {
    update(clickedSquare->getRow(), clickedSquare->getCol(), 0);
    sudoku->setValueAt(clickedSquare->getRow(), clickedSquare->getCol(), 0);
  }
}

void MainWindow::updateClock() {
    if (gameFinished || gamePaused)
        return;

    Time elapsedTime = clock->getElapsedTime() - totalPausedTime;
    int seconds = elapsedTime.asSeconds();
    int minutes = seconds / 60;
    seconds %= 60;
    clockText.setString((minutes < 10 ? "0" : "") + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds));
}

void MainWindow::update(int rowClicked, int colClicked, int valueClicked)
{
  if (clickedSquare == nullptr)
    return;

  int boxX = colClicked / sudoku->getBoxSize();
  int boxY = rowClicked / sudoku->getBoxSize();
  for (auto &row : sudokuSquares)
  {
    for (auto &square : row)
    {
      if (square->getRow() == rowClicked && square->getCol() == colClicked)
        continue;
      if (square->getRow() == rowClicked || square->getCol() == colClicked || (square->getRow() / sudoku->getBoxSize() == boxY && square->getCol() / sudoku->getBoxSize() == boxX))
      {
        if (square->getValue() == valueClicked && square->getValue() != 0)
          square->update(SudokuSquare::INCORRECT);
        else
          square->update(SudokuSquare::HOVERED);
      }
      else if (square->getValue() == valueClicked && square->getValue() != 0)
        square->update(SudokuSquare::CLICKED);
      else
        square->update(SudokuSquare::IDLE);
    }
  }

  if (clickedSquare->getValueConstant())
    return;
  clickedSquare->setValue(valueClicked);
  sudoku->setValueAt(rowClicked, colClicked, valueClicked);

  if (sudoku->isSolved())
  {
    gameFinished = true;
    animationFinished = false;
    animationStage = 0;
    cout << "Game finished!" << endl;
  }
}

void MainWindow::onAnimationStageChanged()
{
  if (animationStage < 9)
  {
    Color flashColor;
    switch (animationStage % 3)
    {
    case 0:
      flashColor = Color::Green; break;
    case 1:
      flashColor = Color::Yellow; break;
    case 2:
      flashColor = Color::Red; break;
    }

    for (auto &row : sudokuSquares)
      for (auto &square : row)
        square->setFillColor(flashColor);

    if (clock->getElapsedTime().asMilliseconds() > 500)
    {
      animationStage++;
      clock->restart();
    }
  }
  else
  {
    animationFinished = true;
    for (auto &row : sudokuSquares)
      for (auto &square : row)
        square->setFillColor(Color::White);
  }
}

void MainWindow::onNewGameButtonClicked()
{
  sudoku = new Sudoku(sudoku->getDifficulty(), sudoku->getSize());
  for (auto &row : sudokuSquares) {
    for (auto &square : row)
    {
      square->setValue(sudoku->getValueAt(square->getRow(), square->getCol()));
      square->setValueConstant(sudoku->getValueAt(square->getRow(), square->getCol()) != 0);
    }
  }
  clickedSquare = nullptr;
  gameFinished = false;
  animationFinished = false;
  animationStage = 0;
  clock->restart();
  totalPausedTime = Time::Zero;
  menuButtons[1]->setText("Pause");
}

void MainWindow::onPauseButtonClicked() {
  if (gameFinished)
    return;

  if (gamePaused) {
    // Resume the game
    menuButtons[1]->setText("Pause");
    clock->restart();
    totalPausedTime += clock->getElapsedTime() - pauseStartTime;
  } else {
    // Pause the game
    menuButtons[1]->setText("Resume");
    pauseStartTime = clock->getElapsedTime();
  }

  gamePaused = !gamePaused;
}

void MainWindow::onSolveButtonClicked()
{
  sudoku->solveSudoku();
  for (auto &row : sudokuSquares)
    for (auto &square : row)
      square->setValue(sudoku->getValueAt(square->getRow(), square->getCol()));
  gameFinished = true;
  animationFinished = false;
}

void MainWindow::run()
{
  ContextSettings settings;
  settings.antialiasingLevel = 8;
  RenderWindow window(VideoMode(width, height), "Sudoku", Style::Titlebar | Style::Close, settings);
  Image icon;
  if (!icon.loadFromFile(IMG_PATH_DIR + string("favicon.ico")))
    cout << "Couldn't load the icon 'favicon.ico'. Check if the file exists in " + string(IMG_PATH_DIR) + " directory." << endl;
  else
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  
  while (window.isOpen())
  {
    Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case Event::Closed:
        window.close();
        break;
      case Event::MouseButtonPressed:
        onMouseButtonClicked(Vector2f(event.mouseButton.x, event.mouseButton.y));
        break;
      case Event::MouseMoved:
        onMouseMoved(Vector2f(event.mouseMove.x, event.mouseMove.y));
        break;
      case Event::TextEntered:
        onKeyButtonClicked(event.text);
        break;
      case Event::KeyPressed:
        if (event.key.code == Keyboard::Backspace)
          onBackspaceButtonClicked();
        break;
      }
    }
    if (gameFinished && !animationFinished)
      onAnimationStageChanged();

    window.clear(Color(255, 255, 255, 1));
    window.draw(playerText);
    window.draw(difficultyText);
    window.draw(clockText);

    for (auto &button : menuButtons)
      button->draw(&window);

    for (auto &row : sudokuSquares)
      for (auto &square : row)
        square->draw(&window, RenderStates::Default);

    updateClock();
    window.display();
  }
}
