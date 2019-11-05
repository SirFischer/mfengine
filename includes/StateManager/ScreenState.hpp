#pragma once

#include "Window.hpp"

namespace mf
{

class ScreenState
{
public:
	enum class ReturnCtrl{
		END,
		GAME,
		MENU,
		OPTIONS
	};

	virtual ~ScreenState(){}
	ReturnCtrl			run();
	virtual void		update() = 0;
	virtual void		handle_events() = 0;
	virtual void		render() = 0;
	
protected:
	sf::Clock		mGameLoop;
	sf::Time		mElapsedTime;
	Window			*mWindow;
	float			mDeltaTime = 1.f/64.f;
	int				mFPS;
	float			mFrameTime;
	bool			mRunning = true;
	ReturnCtrl		mReturn = ReturnCtrl::END;

	void				calculateFPS(sf::Time timeDiff);
	void				setDeltaTime(float deltatime);
};

}
