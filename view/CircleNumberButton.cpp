#include "CircleNumberButton.h"

CircleNumberButton::CircleNumberButton(int number, const Vector2f &position, float radius, const Font &font, unsigned int characterSize)
    : button(radius), label(to_string(number), font, characterSize), number(number)
{
  // Setup the button
  button.setOrigin(radius, radius);
  button.setPosition(position);
  button.setFillColor(Color::White);
  button.setOutlineColor(Color::Black);
  button.setOutlineThickness(2);

  // Setup the label
  label.setFillColor(Color::Black);

  // Center the text on the button
  FloatRect textRect = label.getLocalBounds();
  label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  label.setPosition(position);
}

int CircleNumberButton::getNumber() const
{
  return number;
}

void CircleNumberButton::draw(RenderWindow *window) const
{
  window->draw(button);
  window->draw(label);
}

bool CircleNumberButton::isClicked(const Vector2f &mousePosition) const
{
  return button.getGlobalBounds().contains(mousePosition);
}
