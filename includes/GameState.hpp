#pragma once

#include "ScreenState.hpp"
#include "ResourceManager.hpp"
#include "Mesh.hpp"
#include <math.h>

#define DELTATIME		1.f/64.f

class GameState : public mf::ScreenState
{
private:
	//TEST
	float	vertex[18] = {
		-0.5, 0.0, 1.0,
		0.0, 1, 1.0,
		0.5, 0.0, 1.0,
		-0.5, 0.0, 1.0,
		0.5, 0.0, 1.0,
		0.0, -1.0, 1.0
	};

	mf::ResourceManager		mResourceManager;
	mf::Mesh				mesh;

public:
	explicit GameState(mf::Window *tWindow);
	~GameState();

	mf::ScreenState::ReturnCtrl		run();
	void							update();
	void							handle_events();
	void							render();
};
