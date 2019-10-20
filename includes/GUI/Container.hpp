#include "Window.hpp"

namespace MFGUI
{
	class Container
	{
	protected:
		Window			*mWindow;
		sf::Drawable	*mContainer;
	public:
		virtual 		~Container(){}
		virtual void	Draw() = 0;
	};
}
