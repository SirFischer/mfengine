#pragma once

#include <stack>
#include "screen_states.hpp"

class state_manager
{
private:
	std::stack<screen_state *>	states;
public:
	state_manager();
	~state_manager();

	void		state_pop();
	void		state_push();
	void		run();
};
