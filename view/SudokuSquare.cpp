#include "SudokuSquare.h"

/**
 * @param rowOnBoard Y-position on the board
 * @param colOnBoard X-position on the board
 * @param x window position
 * @param y window position
 * @param width width of square in pixels
 * @param height height of square in pixels
 * @param font font needed to generate text within a square
 * @param text value to be stored
 */
SudokuSquare::SudokuSquare(int rowOnBoard, int colOnBoard, float x, float y, float size, const Font &font, const string &text)
{
	m_row = rowOnBoard;
	m_col = colOnBoard;

	setSize(Vector2f(size, size));
	setPosition(Vector2f(x, y));
	setOutlineThickness(1);
	setOutlineColor(Color::Black);

	int fontSize;
	if (size < 50)
		fontSize = 16;
	else
		fontSize = 24;

	m_font = font;
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setFillColor(Color::Black);
	m_text.setCharacterSize(fontSize);

	m_text.setPosition(
			getPosition().x + getGlobalBounds().width / 3.f - m_text.getGlobalBounds().width / 2.f,
			getPosition().y + getGlobalBounds().height / 3.f - m_text.getGlobalBounds().height / 2.f);

	m_idleColor = Color::White;
	m_hoverColor = Color(224, 255, 255);
	m_clickedColor = Color(135, 206, 235);
	m_incorrectColor = Color(220, 20, 6);
	m_activeColor = m_idleColor;
	setFillColor(m_activeColor);

	m_value = 0;
	m_isValueConstant = false;
	m_state = IDLE;
}

/**
 * @brief Draws this object with given states at given target
 * @param target pointer to draw at
 * @param states states for print object at <code>RenderTarget</code>
 */
void SudokuSquare::draw(RenderTarget *target, RenderStates states) const
{
	target->draw(*this, states);
	target->draw(m_text);
}

int SudokuSquare::getRow()
{
	return m_row;
}

int SudokuSquare::getCol()
{
	return m_col;
}

void SudokuSquare::setValue(int value)
{
	m_value = value;
	if (value != 0)
		m_text.setString(to_string(value));
	else
		m_text.setString("");
}

int SudokuSquare::getValue()
{
	return m_value;
}

void SudokuSquare::setValueConstant(bool valueConstant)
{
	m_isValueConstant = valueConstant;
}

bool SudokuSquare::getValueConstant()
{
	return m_isValueConstant;
}

void SudokuSquare::update(SquareState newState)
{
	switch (newState)
	{
	case IDLE:
		m_activeColor = m_idleColor;
		break;
	case HOVERED:
		m_activeColor = m_hoverColor;
		break;
	case CLICKED:
		m_activeColor = m_clickedColor;
		break;
	case INCORRECT:
		m_activeColor = m_incorrectColor;
		break;
	}
	m_state = newState;
	setFillColor(m_activeColor);
}
