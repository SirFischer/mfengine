#include "aContainerItem.hpp"

namespace mf
{
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
			mMouseState = (outside) ? MouseState::EXITED : (sf::Mouse::isButtonPressed(sf::Mouse::Left)) ? MouseState::CLICKED : MouseState::INSIDE;
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
	}
	
	void		aContainerItem::SetPosition(sf::Vector2f position)
	{
		mSprite.setPosition(position);
	}

	void		aContainerItem::SetScale(sf::Vector2f scale)
	{
		mSprite.setScale(scale);
	}
}
