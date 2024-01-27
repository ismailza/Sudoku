#ifndef SUDOKUSQUARE_H
#define SUDOKUSQUARE_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class SudokuSquare final : public RectangleShape
{
public:
	enum SquareState
	{
		IDLE,
		HOVERED,
		CLICKED,
		INCORRECT
	};
	SudokuSquare(int rowOnBoard, int colOnBoard, float x, float y, float size, const Font &font, const string &text);
	void draw(RenderTarget *target, RenderStates states = RenderStates::Default) const;
	void setValue(int value);
	int getValue();
	void setValueConstant(bool valueConstant);
	bool getValueConstant();
	int getRow();
	int getCol();
	void update(SquareState newState);

private:
	int m_row, m_col; // Position on the board
	Text m_text;			// Text that contains the numeric value of square
	Font m_font;

	Color m_idleColor;
	Color m_clickedColor;
	Color m_hoverColor;
	Color m_incorrectColor;
	Color m_activeColor;

	SquareState m_state;		// Current state of a square
	int m_value;						// Numeric value of number within this square or 0 if there is no number
	bool m_isValueConstant; // True if value within this square can be modified
};

#endif // SUDOKUSQUARE_H