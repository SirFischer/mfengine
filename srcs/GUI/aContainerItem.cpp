#include "aContainerItem.hpp"

namespace mf
{

	aContainerItem::aContainerItem()
	{

	}

	void		aContainerItem::UpdateState()
	{
		bool			outside;
		sf::Vector2i	mousePos;
		sf::Vector2f	conPos;
		sf::Vector2f	size;

		size = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
		conPos = mSprite.getPosition();
		mousePos = mWindow->getRelMousePos();
		outside = (mousePos.x > conPos.x + size.x|| mousePos.y > conPos.y + size.y || mousePos.x < conPos.x || mousePos.y < conPos.y);
		switch (mMouseState)
		{
		case MouseState::INSIDE:
			mMouseState = (outside) ? MouseState::EXITED : (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mPrevLeftMouseButtonState) ? MouseState::CLICKED : MouseState::INSIDE;
			break;
		case MouseState::OUTSIDE:
			mMouseState = (outside) ? MouseState::OUTSIDE : MouseState::ENTERED;
			break;
		case MouseState::CLICKED:
			mMouseState = (outside || !sf::Mouse::isButtonPressed(sf::Mouse::Left)) ? MouseState::OUTSIDE : MouseState::CLICKED;
			break;
		default:
			mMouseState = (outside) ? MouseState::OUTSIDE : MouseState::INSIDE;
			break;
		}
		mPrevLeftMouseButtonState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}
	
	void		aContainerItem::SetPosition(sf::Vector2f position)
	{
		if (mPlacement == ContainerPlacement::ABSOLUTE || !mParent)
			mPosition = position;
		else
			mPosition = mParent->GetPosition() + position;
		mSprite.setPosition(mPosition);
	}

	void		aContainerItem::SetScale(sf::Vector2f scale)
	{
		mSprite.setScale(scale);
	}

	void		aContainerItem::SetSize(sf::Vector2f size)
	{
		mSize = size;
	}

	void		aContainerItem::SetSize(float x, float y)
	{
		mSize = sf::Vector2f(x, y);
	}

	void		aContainerItem::SetParent(aContainerItem *item)
	{
		mParent = item;
	}

	void		aContainerItem::SetPlacement(ContainerPlacement placement)
	{
		mPlacement = placement;
		SetPosition(mPosition);
	}

	void		aContainerItem::SetFontSize(int tSize)
	{
		mText.setCharacterSize(tSize);
	}

	void		aContainerItem::SetFont(sf::Font tFont)
	{
		mFont = tFont;
		mText.setFont(mFont);
	}

	void		aContainerItem::SetColor(sf::Color tColor)
	{
		mSprite.setColor(tColor);
	}

	void	aContainerItem::SetBackground(int tWidth, int tHeight, sf::Color tColor)
	{
		sf::Image	img;
		img.create(tWidth, tHeight, tColor);
		mSize.x = tWidth;
		mSize.y = tHeight;
		mTexture.loadFromImage(img);
		mSprite.setTexture(mTexture);
	}
	void	aContainerItem::SetBackground(sf::Vector2f tSize, sf::Color tColor)
	{
		SetBackground(tSize.x, tSize.y, tColor);
	}
	void	aContainerItem::SetBackground(sf::Color tColor)
	{
		SetBackground(mSize.x, mSize.y, tColor);
	}
	void	aContainerItem::SetBackground()
	{
		SetBackground(mSize.x, mSize.y, sf::Color::White);
	}

	void	aContainerItem::SetView()
	{
		mLastView = mWindow->getView();
		mView.reset(sf::FloatRect(mPosition.x, mPosition.y, mSize.x, mSize.y));
		mView.setViewport(sf::FloatRect(mPosition.x / mWindow->getSize().x, mPosition.y / mWindow->getSize().y, mSize.x / mWindow->getSize().x, mSize.y / mWindow->getSize().y));
		mWindow->setView(mView);
	}
	
	void	aContainerItem::ResetView()
	{
		mWindow->setView(mLastView);
	}

	void	aContainerItem::SetOverflowMode(OverflowMode tMode)
	{
		mOverFlowMode = tMode;
	}
}
