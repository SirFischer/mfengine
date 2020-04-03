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
		sf::Vector2f			mTextPos;

	public:
						Button(Window *tWindow);
						~Button();

		void			Draw();
		void			Update();

		void			SetFont(std::string path);
		void			SetText(std::string text);
		void			SetTextOffset(sf::Vector2f offset);
		void			SetTextSize(unsigned int size);
	};
}
