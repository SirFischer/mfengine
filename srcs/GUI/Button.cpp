#include "Button.hpp"

mf::Button::Button(Window *tWindow, mf::ResourceManager *tResourceManager)
{
	mWindow = tWindow;
	mResourceManager = tResourceManager;
	mDefaultTexture.loadFromImage(mResourceManager->LoadImage("assets/textures/GUI/Button_1.png"), sf::IntRect(1, 0, 28, 18));
	mOnHoverTexture.loadFromImage(mResourceManager->LoadImage("assets/textures/GUI/Button_1.png"), sf::IntRect(1, 0, 28, 18));
	mOnClickTexture.loadFromImage(mResourceManager->LoadImage("assets/textures/GUI/Button_1.png"), sf::IntRect(33, 0, 28, 18));
	mContainer.setTexture(mDefaultTexture);
}

mf::Button::~Button()
{
}

void	mf::Button::Draw()
{
	mWindow->draw(&mContainer);
}

void	mf::Button::Update()
{
	this->UpdateState();
	if (mMouseState == MouseState::CLICKED)
		mContainer.setTexture(mOnClickTexture);
	else if (mMouseState == MouseState::INSIDE || mMouseState == MouseState::ENTERED)
		mContainer.setTexture(mOnHoverTexture);
	else
		mContainer.setTexture(mDefaultTexture);
}