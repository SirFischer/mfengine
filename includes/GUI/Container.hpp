#include "Window.hpp"

namespace MFGUI
{
	enum class MouseState
	{
		OUTSIDE,
		INSIDE,
		ENTERED,
		EXITED,
		CLICKED
	};
	class Container
	{
	protected:
		Window			*mWindow = NULL;
		sf::Drawable	*mContainer = NULL;
		MouseState		mMouseState = MouseState::OUTSIDE;
	public:
		virtual 		~Container(){}
		virtual void	Draw() = 0;
		virtual void	Update() = 0;
	};
}
