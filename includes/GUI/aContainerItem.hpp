#include "Window.hpp"
#include <iostream>

namespace mf
{
	enum class MouseState
	{
		OUTSIDE,
		INSIDE,
		ENTERED,
		EXITED,
		CLICKED
	};

	enum class ContainerPlacement
	{
		ABSOLUTE,
		RELATIVE
	};

	enum class OverflowMode
    {
        HORIZONTAL_SCROLL,
        VERTICAL_SCROLL,
        HIDDEN
    };

	class aContainerItem
	{
	protected:
		Window						*mWindow = NULL;
		sf::Sprite					mSprite;
		sf::View					mView;
		sf::View					mLastView;
		sf::Texture					mTexture;
		sf::Font            		mFont;
    	sf::Text            		mText;
		sf::Vector2f				mPosition = sf::Vector2f(0, 0);
		sf::Vector2f       	 		mSize = sf::Vector2f(200, 100);
		aContainerItem				*mParent = NULL;
		ContainerPlacement			mPlacement = ContainerPlacement::RELATIVE;
		MouseState					mMouseState = MouseState::OUTSIDE;
		OverflowMode       			mOverFlowMode = OverflowMode::HIDDEN;
		void						UpdateState();
		bool						mPrevLeftMouseButtonState = false;

	public:
									aContainerItem();
		virtual 					~aContainerItem(){}
		virtual void				Draw() = 0;
		virtual void				Update() = 0;

		MouseState					GetState(){return (mMouseState);}
		sf::Vector2f				GetPosition(){return (mPosition);}

		void						SetPosition(sf::Vector2f position);
		void						SetScale(sf::Vector2f scale);
		void						SetSize(sf::Vector2f size);
		void						SetSize(float x, float y);
		void						SetParent(aContainerItem *item);
		void						SetPlacement(ContainerPlacement placement);
		void						SetFontSize(int tSize);
		void						SetFontColor(sf::Color tColor);
		void						SetFont(sf::Font tFont);
		void						SetColor(sf::Color tColor);
		void						SetBackground(int tWidth, int tHeight, sf::Color tColor);
		void						SetBackground(sf::Vector2f tSize, sf::Color tColor);
		void						SetBackground(sf::Color tColor);
		void						SetBackground();
		void						SetOverflowMode(OverflowMode tMode);
		void						SetView();
		void						ResetView();
	};
}
