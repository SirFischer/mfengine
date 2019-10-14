#pragma once

# include <SFML/Graphics.hpp>
# include <SFML/OpenGL.hpp>

# define DEFAULT_WIN_HEIGHT		1080
# define DEFAULT_WIN_WIDTH		1920

class window
{
private:
	sf::RenderWindow	mWindow;
	sf::Vector2i		mSize;
	std::string			mTitle;
	bool				mIsFullscreen = false;

	bool				create();
	void				destroy();
	void				initOpengl();
public:
	window();
	window(std::string title, sf::Vector2i size);
	~window();
};