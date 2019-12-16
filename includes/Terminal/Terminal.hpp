#pragma once

#include <string>
#include <cstring>
#include <map>
#include <iterator>
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

	typedef struct	s_terminal_command
	{
		std::function<TERMINAL_ERROR_CODE(Terminal *,std::vector<std::string> params)> cmnd;
		std::string help_short;
		std::string help_long;
	}				t_terminal_command;

	EventHandler						*mEventHandler = NULL;

	std::map<std::string, t_terminal_command>	mCommands;
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

// COMMANDS

Terminal::TERMINAL_ERROR_CODE		Help(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE		UnbindAll(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE		Bind(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE		Toggle(Terminal *term, std::vector<std::string> params);

} // namespace mf
