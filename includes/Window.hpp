#pragma once

# include <SFML/Graphics.hpp>
# include <SFML/OpenGL.hpp>

# define DEFAULT_WIN_HEIGHT		1080
# define DEFAULT_WIN_WIDTH		1920

class Window
{
private:
	sf::RenderWindow	mWindow;
	sf::Vector2i		mSize;
	std::string			mTitle;
	bool				mIsFullscreen = false;

	bool				create();
	void				destroy();
	void				initOpengl();
	void				processEvents();
	
public:
	Window();
	Window(std::string title, sf::Vector2i size);
	~Window();
	
	void				update();
	void				toggleFullscreen();
	void				clear();
	void				clear(sf::Color color);
	void				clear(float r, float g, float b, float a);
	void				draw(sf::Drawable *tDrawable);
	void				display();

	bool				isOpen(){return (mWindow.isOpen());}

	sf::Vector2i		getRelMousePos(){return (sf::Mouse::getPosition(mWindow));}
};