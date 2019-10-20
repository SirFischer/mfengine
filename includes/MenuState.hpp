#pragma once

#include "ScreenState.hpp"
#include "Button.hpp"

#define DELTATIME		1.f/64.f

class MenuState : public ScreenState
{
private:
	MFGUI::Button	*mTestButton;

public:
	MenuState(Window *tWindow);
	~MenuState();

	ReturnCtrl		run();
	void			update();
	void			handle_events();
	void			render();
};

