#pragma once

#include "ScreenState.hpp"
#include "Button.hpp"

#define MENUDELTATIME		1.f/64.f

class MenuState : public ScreenState
{
private:
	mf::Button				*mTestButton[4];
	mf::ResourceManager		mResourceManager;

public:
	MenuState(Window *tWindow);
	~MenuState();

	ReturnCtrl		run();
	void			update();
	void			handle_events();
	void			render();
};

