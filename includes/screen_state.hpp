#pragma once

#include "window.hpp"

class screen_state
{
protected:
	window				*mWindow;

public:
	screen_state(window	*tWindow);

	virtual int			run() = 0;
	virtual void		update() = 0;
	virtual void		handle_events() = 0;
	virtual void		render() = 0;
};


screen_state::screen_state(window *tWindow):
mWindow(tWindow)
{

}