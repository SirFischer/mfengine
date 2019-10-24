#include "Button.hpp"

MFGUI::Button::Button(Window *tWindow)
{
	mWindow = tWindow;
	mDefaultTexture.loadFromFile("assets/textures/GUI/Button_1.png", sf::IntRect(0, 0, 30, 20));
	mOnHoverTexture.loadFromFile("assets/textures/GUI/Button_1.png", sf::IntRect(0, 0, 30, 20));
	mOnClickTexture.loadFromFile("assets/textures/GUI/Button_1.png", sf::IntRect(30, 0, 30, 20));
	mContainer.setTexture(mDefaultTexture);
	mContainer.setScale(3, 3);
}

MFGUI::Button::~Button()
{
}

void	MFGUI::Button::Draw()
{
	mWindow->draw(&mContainer);
}

void	MFGUI::Button::Update()
{
	this->UpdateState();
	if (mMouseState == MouseState::CLICKED)
		mContainer.setTexture(mOnClickTexture);
	else if (mMouseState == MouseState::INSIDE || mMouseState == MouseState::ENTERED)
		mContainer.setTexture(mOnHoverTexture);
	else
		mContainer.setTexture(mDefaultTexture);
}