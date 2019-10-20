#pragma once

#include <SFML/Graphics.hpp>

#include "Container.hpp"
#include "Window.hpp"

namespace MFGUI
{
	class Button : public Container
	{
	private:
	public:
		Button(Window *tWindow);
		~Button();

		void	Draw();
	};
}
