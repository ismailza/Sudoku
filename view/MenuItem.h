#ifndef MENUITEM_H
#define MENUITEM_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class MenuItem
{
private:
  Text text;

public:
  MenuItem(const string &, Font &, unsigned int);
  void setPosition(float, float);
  void setText(const string &);
  Text &getText();
  void setHighlight(bool);
};

#endif // MENUITEM_H