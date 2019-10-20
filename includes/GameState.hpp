#pragma once

#include "ScreenState.hpp"

#define DELTATIME		1.f/64.f

class GameState : public ScreenState
{
public:
	GameState(Window *tWindow);
	~GameState();

	ReturnCtrl		run();
	void			update();
	void			handle_events();
	void			render();
};
