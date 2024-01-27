#include "Menu.h"

Menu::Menu() : selectedItemIndex(0) {}

void Menu::addItem(const MenuItem &item)
{
  items.push_back(item);
  if (items.size() == 1)
    items[0].setHighlight(true);
}

MenuItem &Menu::getItem(int index)
{
  return items[index];
}

void Menu::handleInput(Keyboard::Key key)
{
  items[selectedItemIndex].setHighlight(false);
  if (key == Keyboard::Up)
  {
    if (selectedItemIndex == 0)
      selectedItemIndex = items.size() - 1;
    else
      selectedItemIndex--;
  }
  else if (key == Keyboard::Down)
  {
    if (selectedItemIndex == items.size() - 1)
      selectedItemIndex = 0;
    else
      selectedItemIndex++;
  }
  items[selectedItemIndex].setHighlight(true);
}

void Menu::clear()
{
  for (auto &item : items)
    items.pop_back();
  selectedItemIndex = 0;
}

void Menu::draw(RenderWindow &window)
{
  for (auto &item : items)
    window.draw(item.getText());
}

int Menu::getSelectedItemIndex() const
{
  return selectedItemIndex;
}

int Menu::getSize()
{
  return items.size();
}