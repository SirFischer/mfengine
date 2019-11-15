#pragma once

#include <string>
#include <cstring>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>

#include "EventHandler.hpp"

namespace mf
{

class Terminal
{
public:
	enum class	TERMINAL_ERROR_CODE
	{
		SUCCESS,
		BAD_COMMAND,
		BAD_CONTEXT,
		BAD_ARGUMENTS,
		EMPTY_COMMAND
	};
	
	EventHandler						*mEventHandler = NULL;

	std::map<std::string, std::function<TERMINAL_ERROR_CODE(Terminal *,std::vector<std::string> params)>>		mCommands;
	std::map<std::string, ACTION>				mActions;
	std::map<std::string, sf::Keyboard::Key>	mKeys;

	void								LoadCommands();
	void								LoadActions();
	void								LoadKeys();

	Terminal(/* args */);
	~Terminal();

	TERMINAL_ERROR_CODE					ProcessCommand(std::string line);
	TERMINAL_ERROR_CODE					ReadFromFile(std::string path);

};

} // namespace mf



