#include "game_state.hpp"

game_state::game_state(/* args */)
{
}

game_state::~game_state()
{
}

int		game_state::run()
{
	sf::Time	elapsedTime;

	elapsedTime = sf::seconds(DELTATIME);
	while (mWindow->isOpen())
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
}
