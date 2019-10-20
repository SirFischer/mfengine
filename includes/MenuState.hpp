#pragma once

#include "ScreenState.hpp"

#define DELTATIME		1.f/64.f

class MenuState : public ScreenState
{
public:
	MenuState(Window *tWindow);
	~MenuState();

	ReturnCtrl		run();
	void			update();
	void			handle_events();
	void			render();
};

