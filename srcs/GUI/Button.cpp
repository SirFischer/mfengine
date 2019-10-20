#include "Button.hpp"

MFGUI::Button::Button(Window *tWindow)
{
	mWindow = tWindow;
	mContainer = new sf::RectangleShape(sf::Vector2f(100, 100));
	((sf::RectangleShape *)mContainer)->setFillColor(sf::Color::Red);
}

MFGUI::Button::~Button()
{
	delete mContainer;
}

void	MFGUI::Button::Draw()
{
	mWindow->draw(mContainer);
}

void	MFGUI::Button::Update()
{
	bool			outside;
	sf::Vector2i	mousePos;
	sf::Vector2f	conPos;
	sf::Vector2f	size;

	size = ((sf::RectangleShape *)mContainer)->getSize();
	conPos = ((sf::RectangleShape *)mContainer)->getPosition();
	mousePos = mWindow->getRelMousePos();
	outside = (mousePos.x > conPos.x + size.x|| mousePos.y > conPos.y + size.y || mousePos.x < conPos.x || mousePos.y < conPos.y);
	switch (mMouseState)
	{
	case MouseState::INSIDE:
		mMouseState = (outside) ? MouseState::EXITED : MouseState::INSIDE;
		break;
	case MouseState::OUTSIDE:
		mMouseState = (outside) ? MouseState::OUTSIDE : MouseState::ENTERED;
		break;
	default:
		mMouseState = (outside) ? MouseState::OUTSIDE : MouseState::INSIDE;
		break;
	}
	printf("%d\n", (int)mMouseState);
}