#include "MenuItem.h"

MenuItem::MenuItem(const string &str, Font &font, unsigned int charSize)
{
  text.setFont(font);
  text.setString(str);
  text.setCharacterSize(charSize);
  text.setFillColor(Color::White);
}

void MenuItem::setPosition(float x, float y)
{
  text.setPosition(x, y);
}

void MenuItem::setText(const string &str)
{
  text.setString(str);
}

Text &MenuItem::getText()
{
  return text;
}

void MenuItem::setHighlight(bool flag)
{
  if (flag)
    text.setFillColor(Color::Red);
  else
    text.setFillColor(Color::White);
}