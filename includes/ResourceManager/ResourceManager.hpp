#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Shader.hpp"

namespace mf
{
	class ResourceManager
	{
	private:
		ResourceManager();
		~ResourceManager();

		static std::map<std::string, sf::Font>		mFonts;
		static std::map<std::string, sf::Image>		mImages;
		static std::map<std::string, mf::Shader>	mShaders;

	public:
		
		static bool				verbose;

		static sf::Image		LoadImage(std::string path);
		static sf::Font			LoadFont(std::string path);
		static void				LoadShader(std::string name, std::string vertex, std::string fragment);

		static mf::Shader		*GetShader(std::string name);
	};
}
