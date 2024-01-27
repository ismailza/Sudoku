#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <fcntl.h>

#include "Game.h"

Game::Game() : width(800), height(500), currentDifficulty(Difficulty::Easy), soundEnabled(true), musicEnabled(true), currentSize(Size::Medium)
{
  if (!backgroundTexture.loadFromFile(IMG_PATH_DIR + string("background.png")))
    throw runtime_error("Couldn't load the background image 'background.png'. Check if the file exists in " + string(IMG_PATH_DIR) + " directory.");
  backgroundSprite.setTexture(backgroundTexture);

  if (!menuFont.loadFromFile(FONT_PATH_DIR + string("BungeeShade-Regular.ttf")))
    throw runtime_error("Couldn't load the font file. Check if the file exists in " + string(FONT_PATH_DIR) + " directory.");

  window.create(VideoMode(width, height), "Sudoku", Style::Titlebar | Style::Close);
  if (!icon.loadFromFile(IMG_PATH_DIR + string("favicon.ico")))
    cout << "Couldn't load the icon 'favicon.ico'. Check if the file exists in " + string(IMG_PATH_DIR) + " directory." << endl;
  else
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  if (!backgroundMusic.openFromFile(SOUND_PATH_DIR + string("ravel.ogg")))
    cout << "Couldn't load the background music 'ravel.ogg'. Check if the file exists in " + string(SOUND_PATH_DIR) + " directory." << endl;
  else
  {
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
  }

  if (!clickSoundBuffer.loadFromFile(SOUND_PATH_DIR + string("click.wav")))
    cout << "Couldn't load the click sound 'click.wav'. Check if the file exists in " + string(SOUND_PATH_DIR) + " directory." << endl;
  else
    clickSound.setBuffer(clickSoundBuffer);
  
  playerName = "Player";
  playerNameText = Text(playerName, menuFont);
  playerNameText.setCharacterSize(24);
  playerNameText.setFillColor(Color::White);
  playerNameText.setPosition(130.0f, 250.0f);
  isNameInputActive = false;

  nameInputField = FloatRect(125.0f, 250.0f, 180.0f, 30.0f);
  inputBox = RectangleShape(Vector2f(nameInputField.width, nameInputField.height));
  inputBox.setPosition(nameInputField.left, nameInputField.top);
  inputBox.setFillColor(Color::Transparent);
  inputBox.setOutlineColor(Color::White);
  inputBox.setOutlineThickness(1.0f);  
  
  setupMenu();
  setupOptionsMenu();
  currentState = MenuState::MainMenu;
}

void Game::setupMenu()
{
  mainMenu.addItem(MenuItem("Play", menuFont, 28));
  mainMenu.addItem(MenuItem("Options", menuFont, 28));
  mainMenu.addItem(MenuItem("Exit", menuFont, 28));

  int size = mainMenu.getSize();
  float y = 300.0f;
  for (int i = 0; i < size; ++i)
  {
    mainMenu.getItem(i).setPosition(160.0f, y);
    y += 40.0f;
  }
}

void Game::setupOptionsMenu()
{
  optionsMenu.addItem(MenuItem("Difficulty : " + difficultyToString(currentDifficulty), menuFont, 22));
  optionsMenu.addItem(MenuItem("Sound : " + string(soundEnabled ? "On" : "Off"), menuFont, 22));
  optionsMenu.addItem(MenuItem("Music : " + string(musicEnabled ? "On" : "Off"), menuFont, 22));
  optionsMenu.addItem(MenuItem("Size : " + sizeToString(currentSize), menuFont, 22));

  int size = optionsMenu.getSize();
  float y = 300.0f;
  for (int i = 0; i < size; ++i)
  {
    optionsMenu.getItem(i).setPosition(120.0f, y);
    y += 40.0f;
  }
}

void Game::handleMainMenuInput(const Event &event)
{
  if (event.key.code == Keyboard::Enter)
  {
    mainMenu.handleInput(event.key.code);
    switch (mainMenu.getSelectedItemIndex())
    {
    case 0:
      window.close();
      mainWindow = new MainWindow(static_cast<int>(currentDifficulty), getSize(currentSize), playerName);
      mainWindow->run();
      break;
    case 1:
      currentState = MenuState::OptionsMenu;
      break;
    case 2:
      window.close();
      break;
    }
  }
}

void Game::handleOptionsMenuInput(const Event &event)
{
  if (event.key.code == Keyboard::Escape)
    currentState = MenuState::MainMenu;
  else if (event.key.code == Keyboard::Enter || event.key.code == Keyboard::Space || event.key.code == Keyboard::Key::Right || event.key.code == Keyboard::Key::Left)
  {
    optionsMenu.handleInput(event.key.code);
    int selectedIndex = optionsMenu.getSelectedItemIndex();
    switch (selectedIndex)
    {
    case 0: // Toggle difficulty
      if (event.key.code == Keyboard::Key::Left)
        currentDifficulty = static_cast<Difficulty>((static_cast<int>(currentDifficulty) + 2) % 3);
      else
        currentDifficulty = static_cast<Difficulty>((static_cast<int>(currentDifficulty) + 1) % 3);
      optionsMenu.getItem(selectedIndex).setText("Difficulty : " + difficultyToString(currentDifficulty));
      break;
    case 1: // Toggle sound
      soundEnabled = !soundEnabled;
      optionsMenu.getItem(selectedIndex).setText("Sound : " + string(soundEnabled ? "On" : "Off"));
      break;
    case 2: // Toggle music
      musicEnabled = !musicEnabled;
      musicEnabled ? backgroundMusic.play() : backgroundMusic.stop();
      optionsMenu.getItem(selectedIndex).setText("Music : " + string(musicEnabled ? "On" : "Off"));
      break;
    case 3: // Toggle size
      if (event.key.code == Keyboard::Key::Left)
        currentSize = static_cast<Size>((static_cast<int>(currentSize) + 2) % 3);
      else
        currentSize = static_cast<Size>((static_cast<int>(currentSize) + 1) % 3);
      optionsMenu.getItem(selectedIndex).setText("Size : " + sizeToString(currentSize));
      break;
    }
  }
}

string Game::difficultyToString(Difficulty difficulty)
{
  if (difficulty == Difficulty::Easy)
    return "Easy";
  else if (difficulty == Difficulty::Medium)
    return "Medium";
  return "Hard";
}

string Game::sizeToString(Size size)
{
  if (size == Size::Small)
    return "4x4";
  else if (size == Size::Medium)
    return "9x9";
  return "16x16";
}

int Game::getSize(Size size)
{
  if (size == Size::Small)
    return 4;
  else if (size == Size::Medium)
    return 9;
  return 16;
}

void Game::run()
{
  while (window.isOpen())
  {
    Event event;
    while (window.pollEvent(event))
    {
      if (event.type == Event::Closed)
        window.close();
      else if (event.type == Event::KeyPressed)
      {
        soundEnabled ? clickSound.play() : clickSound.stop();
        mainMenu.handleInput(event.key.code);
        optionsMenu.handleInput(event.key.code);
        if (currentState == MenuState::MainMenu)
          handleMainMenuInput(event);
        else if (currentState == MenuState::OptionsMenu)
          handleOptionsMenuInput(event);
      }

      if (isNameInputActive)
        handleNameInput(event);

      else if (event.type == Event::MouseButtonPressed)
      {
        if (event.mouseButton.button == Mouse::Left)
        {
          Vector2i mousePos = Mouse::getPosition(window);
          if (nameInputField.contains(mousePos.x, mousePos.y))
            isNameInputActive = true;
          else
            isNameInputActive = false;
        }
      }
    }
    window.clear();
    window.draw(backgroundSprite);
    window.draw(inputBox);
    window.draw(playerNameText);
    if (currentState == MenuState::MainMenu)
      mainMenu.draw(window);
    else if (currentState == MenuState::OptionsMenu)
      optionsMenu.draw(window);
    window.display();
  }
}

void Game::handleNameInput(const Event &event)
{
  if (event.type == Event::TextEntered)
  {
    if (event.text.unicode < 128)
    {
      char enteredChar = static_cast<char>(event.text.unicode);
      if (isalnum(enteredChar) || isspace(enteredChar)) {
        if (playerName.length() < 12)
          playerName.push_back(enteredChar);
      }
      else if (enteredChar == '\b' && playerName.size() > 0)
        playerName.pop_back();
      playerNameText.setString(playerName);
    }
  }
}
