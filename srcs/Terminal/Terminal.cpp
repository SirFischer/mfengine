#include "Terminal.hpp"

namespace mf
{

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
	mCommands.emplace("bind", &Bind);
}

void				Terminal::LoadActions()
{
	mActions["move_backward"] = ACTION::MOVE_BACKWARD;
	mActions["move_forward"] = ACTION::MOVE_FORWARD;
	mActions["move_left"] = ACTION::MOVE_LEFT;
	mActions["move_right"] = ACTION::MOVE_RIGHT;
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
	
	if (!(tmp = strdup(line.c_str())))
		return (TERMINAL_ERROR_CODE::BAD_COMMAND);
	tmp = std::strtok((tmp + line.find_first_not_of(" ")), " ");
	func = tmp;
	tmp = std::strtok(NULL, " ");
	while (tmp)
	{
		params.push_back(tmp);
		tmp = std::strtok(NULL, " ");
	}
	free(tmp);
	if (mCommands.count(func) > 0)
		return (mCommands[func](this, params));
	return (TERMINAL_ERROR_CODE::SUCCESS);
}

}


