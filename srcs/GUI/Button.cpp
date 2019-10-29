#include "Button.hpp"

mf::Button::Button(Window *tWindow, mf::ResourceManager *tResourceManager)
{
	mWindow = tWindow;
	mResourceManager = tResourceManager;
	mDefaultTexture.loadFromImage(mResourceManager->LoadImage("assets/textures/GUI/Button_1.png"), sf::IntRect(1, 0, 28, 18));
	mOnHoverTexture.loadFromImage(mResourceManager->LoadImage("assets/textures/GUI/Button_1.png"), sf::IntRect(1, 0, 28, 18));
	mOnClickTexture.loadFromImage(mResourceManager->LoadImage("assets/textures/GUI/Button_1.png"), sf::IntRect(34, 0, 28, 18));
	mSprite.setTexture(mDefaultTexture);
	mTextPos = sf::Vector2f(10, 10);
}

mf::Button::~Button()
{
}

void	mf::Button::Draw()
{
	mText.setPosition(mSprite.getPosition() + mTextPos);
	mWindow->draw(&mSprite);
	mWindow->draw(&mText);
}

void	mf::Button::Update()
{
	this->UpdateState();
	if (mMouseState == MouseState::CLICKED)
		mSprite.setTexture(mOnClickTexture);
	else if (mMouseState == MouseState::INSIDE || mMouseState == MouseState::ENTERED)
		mSprite.setTexture(mOnHoverTexture);
	else
		mSprite.setTexture(mDefaultTexture);
}



void	mf::Button::SetFont(std::string path)
{
	mFont = mResourceManager->LoadFont(path);
	mText.setFont(mFont);
}

void	mf::Button::SetText(std::string text)
{
	mText.setString(text);
}

void	mf::Button::SetTextOffset(sf::Vector2f offset)
{
	mTextPos = offset;
}