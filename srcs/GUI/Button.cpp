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