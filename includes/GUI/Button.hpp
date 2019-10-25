#pragma once

#include <SFML/Graphics.hpp>

#include "Container.hpp"
#include "Window.hpp"
#include "ResourceManager.hpp"

namespace mf
{
	class Button : public Container
	{
	private:
		sf::Texture				mDefaultTexture;
		sf::Texture				mOnClickTexture;
		sf::Texture				mOnHoverTexture;

		mf::ResourceManager		*mResourceManager;

	public:
						Button(Window *tWindow, mf::ResourceManager *tResourceManager);
						~Button();

		void			Draw();
		void			Update();
	};
}
