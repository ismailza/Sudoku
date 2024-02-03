#ifndef CIRCLENUMBERBUTTON_H
#define CIRCLENUMBERBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class CircleNumberButton
{
private:
  CircleShape button;
  Text label;
  int number;

public:
  CircleNumberButton(int, const Vector2f&, float, const Font&, unsigned int characterSize = 24);
  int getNumber() const;
  void draw(RenderWindow*) const;
  bool isClicked(const Vector2f&) const;
};

#endif // CIRCLENUMBERBUTTON_H