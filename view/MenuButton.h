#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace std;
using namespace sf;

class MenuButton final : public RectangleShape
{
public:
	// Function this button serves
	enum ButtonFunction
	{
		NEW_GAME,
		PAUSE_GAME,
		SOLVE_GAME,
		QUIT_GAME,
		EXIT_GAME
	};
	MenuButton(float x, float y, float width, float height, const Font &font, const string &text, ButtonFunction function);
	ButtonFunction getFunction();
	void draw(RenderTarget *target, RenderStates states = RenderStates::Default) const;
	void update(bool isHovered);
	void setText(const string &text);

private:
	Font m_font;
	Text m_text;
	ButtonFunction m_buttonFunction;
	Color m_activeColor;
	Color m_idleColor;
	Color m_hoverColor;
};

#endif // MENUBUTTON_H