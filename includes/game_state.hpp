#pragma once

#include "screen_state.hpp"

#define DELTATIME		1.f/64.f

class game_state : public screen_state
{
private:
	sf::Clock		mGameLoop;
public:
	game_state();
	~game_state();

	int			run();
	void		update();
	void		handle_events();
	void		render();
};

