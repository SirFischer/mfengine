#pragma once

#include <SFML/Graphics.hpp>

#include "Container.hpp"
#include "Window.hpp"
#include "ResourceManager.hpp"

namespace mf
{
	class Button : public aContainerItem
	{
	private:
		sf::Texture				mDefaultTexture;
		sf::Texture				mOnClickTexture;
		sf::Texture				mOnHoverTexture;
		sf::Font				mFont;
		sf::Text				mText;
		sf::Vector2f			mTextPos;

		mf::ResourceManager		*mResourceManager;

	public:
						Button(Window *tWindow, mf::ResourceManager *tResourceManager);
						~Button();

		void			Draw();
		void			Update();

		void			SetFont(std::string path);
		void			SetText(std::string text);
		void			SetTextOffset(sf::Vector2f offset);
	};
}
