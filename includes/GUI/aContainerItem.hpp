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
	class aContainerItem
	{
	protected:
		Window						*mWindow = NULL;
		sf::Sprite					mSprite;
		MouseState					mMouseState = MouseState::OUTSIDE;
		void						UpdateState();

	public:
		virtual 					~aContainerItem(){}
		virtual void				Draw() = 0;
		virtual void				Update() = 0;

		MouseState					GetState(){return (mMouseState);}
		void						SetPosition(sf::Vector2f position);
		void						SetScale(sf::Vector2f scale);
	};
}
