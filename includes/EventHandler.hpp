#pragma once

#include "Window.hpp"
#include "Actions.hpp"

#include <iostream>
#include <map>

namespace mf
{
class EventHandler
{
private:
	Window								*mWindow;
	std::map<int, bool>	mKeyStateMap;
	std::map<int, ACTION>				mKeyMap;
	std::map<ACTION, bool>				mActionMap;
	std::map<ACTION, bool>				mSubActionMap;
	std::string							mTextInputString;

public:
	EventHandler(Window *tWindow);
	~EventHandler();

	void		HandleEvents();

	bool		GetKeyState(int key);
	bool		GetActionState(ACTION action);
	bool		GetSubActionState(ACTION action);
	void		BindKey(int key, ACTION action);
	void		ToggleAction(ACTION action, bool state);
	void		UnbindAllKeys();

	std::string	GetStringEntered() { return (mTextInputString);}

};

} // namespace mf
