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
	destroy();
}

bool	window::create()
{
	sf::VideoMode mode(mSize.x, mSize.y);

	if (mIsFullscreen && !mode.isValid())
		mode = sf::VideoMode::getFullscreenModes().front();
	mWindow.create(mode, mTitle,
		(mIsFullscreen) ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
	initOpengl();
	return (true);
}

void	window::initOpengl()
{
	glEnable(GL_TEXTURE_2D);
}

void	window::destroy()
{
	mWindow.close();
}

void	window::processEvents()
{
	sf::Event	event;

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			destroy();
		if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F11)
			toggleFullscreen();
	}
}

void	window::update()
{
	processEvents();
}

void	window::toggleFullscreen()
{
	mIsFullscreen = !mIsFullscreen;
	destroy();
	create();
}

void	window::clear()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	window::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	window::clear(sf::Color color)
{
	glClearColor(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.a / 255.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	window::display()
{
	mWindow.display();
}