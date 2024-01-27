#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "MenuItem.cpp"

class Menu
{
private:
  int selectedItemIndex;

public:
  vector<MenuItem> items;
  Menu();
  void addItem(const MenuItem &);
  MenuItem &getItem(int);
  void handleInput(Keyboard::Key);
  void clear();
  int getSize();
  void draw(RenderWindow &);
  int getSelectedItemIndex() const;
};

#endif // MENU_H