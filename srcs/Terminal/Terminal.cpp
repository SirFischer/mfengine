#include "Terminal.hpp"

namespace mf
{

Terminal::Terminal()
{
	LoadCommands();
	LoadActions();
	LoadKeys();
}

Terminal::~Terminal()
{
	if (mHasGUI)
	{
		delete mTextArea;
		delete mTextInput;
		delete mSubmitButton;
		delete mGUI;
	}
}

void				Terminal::LoadCommands()
{
	mCommands.emplace("bind", (t_terminal_command){&Bind, "binds key to action", "..."});
	mCommands.emplace("unbindall", (t_terminal_command){&UnbindAll, "unbind all keys", "..."});
	mCommands.emplace("help", (t_terminal_command){&Help, "Show all commands", "..."});
	mCommands.emplace("toggle", (t_terminal_command){&Toggle, "Toggles an action on or off", "..."});
}

void				Terminal::LoadActions()
{
	mActions["move_backward"]	=	ACTION::MOVE_BACKWARD;
	mActions["move_forward"]	=	ACTION::MOVE_FORWARD;
	mActions["move_left"]		=	ACTION::MOVE_LEFT;
	mActions["move_right"]		=	ACTION::MOVE_RIGHT;
	mActions["toggle_console"]	=	ACTION::TOGGLE_CONSOLE;
	mActions["quit"]			=	ACTION::QUIT;
}

void				Terminal::LoadKeys()
{
	mKeys["a"]					=	sf::Keyboard::A;
	mKeys["d"]					=	sf::Keyboard::D;
	mKeys["s"]					=	sf::Keyboard::S;
	mKeys["w"]					=	sf::Keyboard::W;
	mKeys["esc"]				=	sf::Keyboard::Escape;
	mKeys["tilde"]				=	sf::Keyboard::Tilde;
}

void				Terminal::LoadGUI(Window *tWindow, ResourceManager *tResourceManager, EventHandler *tEventHandler)
{
	mHasGUI = true;
	mGUI = new Container(tWindow);
	mTextArea = new TextBox(tWindow, tResourceManager, tEventHandler);
	mTextInput = new TextBox(tWindow, tResourceManager, tEventHandler);
	mSubmitButton = new Button(tWindow, tResourceManager);
	mGUI->AddItem(mTextArea);
	mGUI->AddItem(mTextInput);
	mGUI->AddItem(mSubmitButton);

}

void				Terminal::UpdateGUI()
{
	if (!mHasGUI)
		return ;
	mGUI->Update();
}

void				Terminal::RenderGUI()
{
	if (!mHasGUI)
		return ;
	mGUI->Draw();
}


Terminal::TERMINAL_ERROR_CODE		Terminal::ProcessCommand(std::string line)
{
	char						*tmp;
	std::string					func;
	std::vector<std::string>	params;
	
	if (line.find("//") != std::string::npos)
		return (TERMINAL_ERROR_CODE::EMPTY_COMMAND);
	if (!(tmp = strdup(line.c_str())))
		return (TERMINAL_ERROR_CODE::BAD_COMMAND);
	if (!(tmp = std::strtok((tmp + line.find_first_not_of(" ")), " ")))
		return (TERMINAL_ERROR_CODE::EMPTY_COMMAND);
	func = tmp;
	tmp = std::strtok(NULL, " ");
	while (tmp)
	{
		params.push_back(tmp);
		tmp = std::strtok(NULL, " ");
	}
	free(tmp);
	if (mCommands.count(func) > 0)
		return (mCommands[func].cmnd(this, params));
	return (TERMINAL_ERROR_CODE::SUCCESS);
}

Terminal::TERMINAL_ERROR_CODE		Terminal::ReadFromFile(std::string path)
{
	std::ifstream			stream(path);
	std::string				line;
	TERMINAL_ERROR_CODE		success = TERMINAL_ERROR_CODE::SUCCESS;
	TERMINAL_ERROR_CODE		tmp;

	while (std::getline(stream, line))
	{
		if ((tmp = ProcessCommand(line)) != TERMINAL_ERROR_CODE::SUCCESS)
			success = tmp;
	}
	return (success);
}

}


