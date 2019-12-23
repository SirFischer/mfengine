#include "Window.hpp"

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

	class aContainerItem
	{
	protected:
		Window						*mWindow = NULL;
		sf::Sprite					mSprite;
		sf::Vector2f				mPosition = sf::Vector2f(0, 0);
		sf::Vector2f       	 		mSize = sf::Vector2f(200, 100);
		aContainerItem				*mParent = NULL;
		ContainerPlacement			mPlacement = ContainerPlacement::RELATIVE;
		MouseState					mMouseState = MouseState::OUTSIDE;
		void						UpdateState();
		bool						mPrevLeftMouseButtonState = false;

	public:
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
	};
}
