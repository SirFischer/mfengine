#pragma once

#include <stack>
#include "ScreenStates.hpp"

class StateManager
{
private:
	std::stack<ScreenState *>	mStates;
	Window						*mWindow;

public:
	explicit StateManager(Window	*tWindow);
	~StateManager();

	void		state_pop();
	void		state_push(ScreenState *state);
	void		run();
};
