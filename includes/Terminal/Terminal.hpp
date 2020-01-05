#pragma once

#include <string>
#include <cstring>
#include <map>
#include <memory>
#include <iterator>
#include <functional>
#include <iostream>
#include <fstream>

#include "EventHandler.hpp"
#include "ResourceManager.hpp"
#include "Window.hpp"
#include "GUI.hpp"

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

	EventHandler								*mEventHandler = NULL;

	std::map<std::string, t_terminal_command>	mCommands;
	std::map<std::string, ACTION>				mActions;
	std::map<std::string, sf::Keyboard::Key>	mKeys;

	Terminal();
	~Terminal();

	TERMINAL_ERROR_CODE							ProcessCommand(std::string line);
	TERMINAL_ERROR_CODE							ReadFromFile(std::string path);

	void										LoadGUI(Window *tWindow, ResourceManager *tResourceManager, EventHandler *tEventHandler);
	void										UpdateGUI();
	void										RenderGUI();

	void										ClearInputGUI();
	void										UpdateOutputStringGUI(std::string tStr);
	std::string									GetOutputStringGUI() {return (mTextArea.get()->GetText());}
	bool										HasGUI() {return (mHasGUI);}

private:
	bool										mHasGUI = false;
	bool										mSubmitReset = true;
	std::unique_ptr<Container>					mGUI;
	std::unique_ptr<TextBox>					mTextArea;
	std::unique_ptr<TextBox>					mTextInput;
	std::unique_ptr<Button>						mSubmitButton;

	void										LoadCommands();
	void										LoadActions();
	void										LoadKeys();

};

// COMMANDS

Terminal::TERMINAL_ERROR_CODE		Help(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE		UnbindAll(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE		Bind(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE		Toggle(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE       Clear(Terminal *term, std::vector<std::string> params);
Terminal::TERMINAL_ERROR_CODE		Execute(Terminal *term, std::vector<std::string> params);

} // namespace mf
