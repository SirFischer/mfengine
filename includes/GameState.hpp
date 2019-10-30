#pragma once

#include "ScreenState.hpp"

#define DELTATIME		1.f/64.f

class GameState : public mf::ScreenState
{
public:
	explicit GameState(mf::Window *tWindow);
	~GameState();

	mf::ScreenState::ReturnCtrl		run();
	void							update();
	void							handle_events();
	void							render();
};
