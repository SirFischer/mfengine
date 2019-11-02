#pragma once

#include "ScreenState.hpp"
#include "ResourceManager.hpp"
#include <math.h>

#define DELTATIME		1.f/64.f

class GameState : public mf::ScreenState
{
private:
	mf::ResourceManager		mResourceManager;

public:
	explicit GameState(mf::Window *tWindow);
	~GameState();

	mf::ScreenState::ReturnCtrl		run();
	void							update();
	void							handle_events();
	void							render();
};
