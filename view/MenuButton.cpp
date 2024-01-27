#include "MenuButton.h"

/**
 * @brief Creates a button with given parameters
 * @param x window position
 * @param y window position
 * @param width width of square in pixels
 * @param height height of square in pixels
 * @param font font needed to generate text within a square
 * @param text value to be stored
 * @param function function this button serves
*/
MenuButton::MenuButton(float x, float y, float width, float height, const Font &font, const string &text, ButtonFunction function)
{
	setSize(Vector2f(width, height));
	setPosition(Vector2f(x, y));
	setOutlineThickness(1);
	setOutlineColor(Color::Black);

	m_idleColor = Color(135, 206, 250);
	m_hoverColor = Color(0, 191, 255);
	m_activeColor = m_idleColor;
	setFillColor(m_activeColor);

	m_font = font;
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setFillColor(Color::Black);
	m_text.setCharacterSize(18);

	m_text.setPosition(
			getPosition().x + getGlobalBounds().width / 3.f - m_text.getGlobalBounds().width / 4,
			getPosition().y + getGlobalBounds().height / 3.f - m_text.getGlobalBounds().height / 4);

	m_buttonFunction = function;
}

MenuButton::ButtonFunction MenuButton::getFunction()
{
	return m_buttonFunction;
}

/**
 * @brief Draws this object with given states at given target
 * @param target pointer to draw at
 * @param states states for print object at <code>RenderTarget</code>
 * @return void
*/
void MenuButton::draw(RenderTarget *target, RenderStates states) const
{
	target->draw(*this, states);
	target->draw(m_text);
}

void MenuButton::update(bool isHovered)
{
	if (isHovered)
		m_activeColor = m_hoverColor;
	else
		m_activeColor = m_idleColor;
	setFillColor(m_activeColor);
}

void MenuButton::setText(const string &text)
{
	m_text.setString(text);
	m_text.setPosition(
			getPosition().x + getGlobalBounds().width / 3.f - m_text.getGlobalBounds().width / 4,
			getPosition().y + getGlobalBounds().height / 3.f - m_text.getGlobalBounds().height / 4);
}