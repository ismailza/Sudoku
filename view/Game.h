#ifndef GAME_H
#define GAME_H

#include "MainWindow.cpp"
#include "Menu.cpp"

class Game
{
private:
  RenderWindow window;
  MainWindow *mainWindow;
  enum class MenuState
  {
    MainMenu,
    OptionsMenu
  };
  enum class Difficulty
  {
    Easy,
    Medium,
    Hard
  };
  enum class Size
  {
    Small,
    Medium,
    Large
  };
  int width;
  int height;
  Image icon;
  Difficulty currentDifficulty;
  Size currentSize;
  bool soundEnabled;
  bool musicEnabled;
  Font menuFont;
  Texture backgroundTexture;
  Sprite backgroundSprite;
  Music backgroundMusic;
  SoundBuffer clickSoundBuffer;
  Sound clickSound;
  Menu mainMenu;
  Menu optionsMenu;
  MenuState currentState;
  FloatRect nameInputField;
  RectangleShape inputBox;
  string playerName;
  Text playerNameText;
  bool isNameInputActive;

  void setupMenu();
  void setupOptionsMenu();
  void handleMainMenuInput(const Event &);
  void handleOptionsMenuInput(const Event &);
  string difficultyToString(Difficulty);
  string sizeToString(Size);
  int getSize(Size);
  void handleNameInput(const Event &);

public:
  Game();
  void run();
};

#endif