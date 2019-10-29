#pragma once

#include "ScreenState.hpp"
#include "Button.hpp"

#define MENUDELTATIME		1.f/64.f

class MenuState : public ScreenState
{
private:
	mf::ResourceManager		mResourceManager;
	mf::Button				mPlayButton;
	mf::Button				mQuitButton;


	void			initButtons();
public:
	explicit MenuState(Window *tWindow);
	~MenuState();

	ReturnCtrl		run();
	void			update();
	void			handle_events();
	void			render();
};

