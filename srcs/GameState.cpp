#include "GameState.hpp"

GameState::GameState(Window *tWindow)
{
	mWindow = tWindow;
}

GameState::~GameState()
{
	
}

GameState::ReturnCtrl	GameState::run()
{
	sf::Time	elapsedTime;

	mRunning = true;
	elapsedTime = sf::seconds(DELTATIME);
	while (mRunning && mWindow->isOpen())
	{
		while (elapsedTime.asSeconds() > DELTATIME)
		{
			handle_events();
			update();
			elapsedTime -= sf::seconds(DELTATIME);
		}
		render();
		elapsedTime += mGameLoop.restart();
	}
	return (mReturn);
}

void				GameState::update()
{
	mWindow->update();
}

void				GameState::handle_events()
{
	
}

void				GameState::render()
{
	mWindow->clear(sf::Color::Red);

	mWindow->display();
}
