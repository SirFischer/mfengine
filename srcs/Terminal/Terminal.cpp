#include "Terminal.hpp"

namespace mf
{

Terminal::TERMINAL_ERROR_CODE		Help(Terminal *term, std::vector<std::string> params)
{
	std::map<std::string, int>::iterator it;

	if (params.size() == 0)
	{
		for (auto const& [key, val] : term->mCommands)
		{
			std::cout << key << " : " << val.help_short << "..." << std::endl;
		}
	}
	else
	{
		std::cout << params.front() << " : " << term->mCommands[params.front()].help_long << std::endl;
	}
	
	(void)params;
	return (Terminal::TERMINAL_ERROR_CODE::SUCCESS);
}

Terminal::TERMINAL_ERROR_CODE		UnbindAll(Terminal *term, std::vector<std::string> params)
{
	(void)params;
	term->mEventHandler->UnbindAllKeys();
	return (Terminal::TERMINAL_ERROR_CODE::SUCCESS);
}

Terminal::TERMINAL_ERROR_CODE		Bind(Terminal *term, std::vector<std::string> params)
{
	if (!term->mEventHandler)
		return (Terminal::TERMINAL_ERROR_CODE::BAD_CONTEXT);
	if (params.size() < 2)
		return (Terminal::TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
	if (term->mKeys.count(params.at(0)) > 0 && term->mActions.count(params.at(1)) > 0)
		term->mEventHandler->BindKey(term->mKeys[params.at(0)], term->mActions[params.at(1)]);
	else
		return (Terminal::TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
	return(Terminal::TERMINAL_ERROR_CODE::SUCCESS);
}

Terminal::Terminal(/* args */)
{
	LoadCommands();
	LoadActions();
	LoadKeys();
}

Terminal::~Terminal()
{
}

void				Terminal::LoadCommands()
{
	mCommands.emplace("bind", (t_terminal_command){&Bind, "binds key to action", "..."});
	mCommands.emplace("unbindall", (t_terminal_command){&UnbindAll, "unbind all keys", "..."});
	mCommands.emplace("help", (t_terminal_command){&Help, "Show all commands", "..."});
}

void				Terminal::LoadActions()
{
	mActions["move_backward"]	=	ACTION::MOVE_BACKWARD;
	mActions["move_forward"]	=	ACTION::MOVE_FORWARD;
	mActions["move_left"]		=	ACTION::MOVE_LEFT;
	mActions["move_right"]		=	ACTION::MOVE_RIGHT;
}

void				Terminal::LoadKeys()
{
	mKeys["a"] = sf::Keyboard::A;
	mKeys["d"] = sf::Keyboard::D;
	mKeys["s"] = sf::Keyboard::S;
	mKeys["w"] = sf::Keyboard::W;
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


