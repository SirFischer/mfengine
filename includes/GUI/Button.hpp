#pragma once

#include <SFML/Graphics.hpp>

#include "Container.hpp"
#include "Window.hpp"

namespace MFGUI
{
	class Button : public Container
	{
	private:
		sf::Texture		mDefaultTexture;
		sf::Texture		mOnClickTexture;
		sf::Texture		mOnHoverTexture;

	public:
						Button(Window *tWindow);
						~Button();

		void			Draw();
		void			Update();
	};
}
