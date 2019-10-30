#pragma once

#include "ScreenState.hpp"
#include "Button.hpp"

#define MENUDELTATIME		1.f/64.f

class MenuState : public mf::ScreenState
{
private:
	mf::ResourceManager		mResourceManager;
	mf::Container			mContainer;
	mf::Button				mPlayButton;
	mf::Button				mOptionsButton;
	mf::Button				mQuitButton;

	mf::Container			mOptionsContainer;

	void			initButtons();
public:
	explicit MenuState(mf::Window *tWindow);
	~MenuState();

	mf::ScreenState::ReturnCtrl	run();
	void						update();
	void						handle_events();
	void						render();
};

