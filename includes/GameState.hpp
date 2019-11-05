#pragma once

#include "ScreenState.hpp"
#include "ResourceManager.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

#include <math.h>

#define DELTATIME		1.f/64.f

class GameState : public mf::ScreenState
{
private:
	//TEST
	float	vertex[18] = {
		0.5, -0.5, -0.5,
		-0.5, 0.5, -0.5,
		-0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, -0.5,
		0.5, -0.5, -0.5
	};

	mf::ResourceManager		mResourceManager;
	mf::Mesh				mesh;
	mf::Camera				mSpectatorCamera;

public:
	explicit GameState(mf::Window *tWindow);
	~GameState();

	mf::ScreenState::ReturnCtrl		run();
	void							update();
	void							handle_events();
	void							render();
};
