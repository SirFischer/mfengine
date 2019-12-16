#pragma once

#include "Window.hpp"
#include "Actions.hpp"

#include <map>

namespace mf
{
class EventHandler
{
private:
	Window							*mWindow;
	std::map<int, ACTION>			mKeyMap;
	std::map<ACTION, bool>			mActionMap;

public:
	EventHandler(Window *tWindow);
	~EventHandler();

	void		HandleEvents();

	bool		GetActionState(ACTION action);
	void		BindKey(int key, ACTION action);
	void		ToggleAction(ACTION action, bool state);
	void		UnbindAllKeys();

};

} // namespace mf
