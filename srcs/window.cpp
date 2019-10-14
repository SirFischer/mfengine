#include "window.hpp"


window::window():
mSize(DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT),
mTitle("Default Window Title")
{
	create();
}

window::window(std::string tTitle, sf::Vector2i tSize):
mSize(tSize),
mTitle(tTitle)
{
	create();
}

window::~window()
{
	create();
}

bool	window::create()
{
	mWindow.create(sf::VideoMode(mSize.x, mSize.y), mTitle,
		(mIsFullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
	initOpengl();
	return (true);
}

void	window::initOpengl()
{
	glEnable(GL_TEXTURE_2D);
}