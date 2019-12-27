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
	mCommands.emplace("clear", (t_terminal_command){&Clear, "Clear terminal", "Clear the terminal output screen"});
	mCommands.emplace("execute", (t_terminal_command){&Execute, "Execute cfg file", "Execute a cfg file"});
}

void				Terminal::LoadActions()
{
	mActions["move_backward"]	=	ACTION::MOVE_BACKWARD;
	mActions["move_forward"]	=	ACTION::MOVE_FORWARD;
	mActions["move_left"]		=	ACTION::MOVE_LEFT;
	mActions["move_right"]		=	ACTION::MOVE_RIGHT;
	mActions["toggle_console"]	=	ACTION::TOGGLE_CONSOLE;
	mActions["quit"]			=	ACTION::QUIT;
	mActions["submit"]			=	ACTION::SUBMIT;
}

void				Terminal::LoadKeys()
{
	mKeys["a"]					=	sf::Keyboard::A;
	mKeys["d"]					=	sf::Keyboard::D;
	mKeys["s"]					=	sf::Keyboard::S;
	mKeys["w"]					=	sf::Keyboard::W;
	mKeys["esc"]				=	sf::Keyboard::Escape;
	mKeys["tilde"]				=	sf::Keyboard::Tilde;
	mKeys["enter"]				=	sf::Keyboard::Enter;
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
	mGUI->SetColorBackground(800, 500, sf::Color(50, 50, 50, 150));
	mGUI->SetPosition(sf::Vector2f(200, 200));

	mSubmitButton->SetPlacement(mf::ContainerPlacement::RELATIVE);
	mSubmitButton->SetPosition(sf::Vector2f(700, 450));
	mSubmitButton->SetScale(sf::Vector2f(4, 3));

	mTextArea->SetPlacement(mf::ContainerPlacement::RELATIVE);
	mTextArea->SetPosition(sf::Vector2f(5, 5));
	mTextArea->SetSize(sf::Vector2f(790, 350));
	mTextArea->SetFontSize(15);
	mTextArea->SetAllowFocus(false);
	tResourceManager->verbose = true;
	mTextArea->SetFont(tResourceManager->LoadFont("assets/fonts/firacode.otf"));

	mTextInput->SetPlacement(mf::ContainerPlacement::RELATIVE);
	mTextInput->SetPosition(sf::Vector2f(5, 470));
	mTextInput->SetSize(sf::Vector2f(690, 50));
	mTextInput->SetFontSize(15);
	mTextInput->SetFont(tResourceManager->LoadFont("assets/fonts/firacode.otf"));
}

void				Terminal::UpdateGUI()
{
	if (!mHasGUI)
		return ;
	if (mEventHandler->GetActionState(ACTION::SUBMIT) || mSubmitButton->GetState() == mf::MouseState::CLICKED)
	{
		if (mSubmitReset)
		{
			ProcessCommand(mTextInput->GetText());
			mTextInput->SetText("");
			mTextArea->SetText(mTextArea->GetText() + '\n');
			mSubmitReset = false;
		}
	}
	else
		mSubmitReset = true;
	mGUI->Update();
}

void				Terminal::RenderGUI()
{
	if (!mHasGUI)
		return ;
	mGUI->Draw();
}

void				Terminal::ClearInputGUI()
{
	if (!mHasGUI)
		return ;
	mTextInput->SetText("");
}

void				Terminal::UpdateOutputStringGUI(std::string tStr)
{
	if (!mTextArea)
		return ;
	mTextArea->SetText(tStr);
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
	if (mHasGUI)
        UpdateOutputStringGUI(GetOutputStringGUI() + func + " is not a valid command...\n");
	return (TERMINAL_ERROR_CODE::BAD_COMMAND);
}

Terminal::TERMINAL_ERROR_CODE		Terminal::ReadFromFile(std::string path)
{
	std::ifstream			stream(path);
	std::string				line;
	TERMINAL_ERROR_CODE		success = TERMINAL_ERROR_CODE::SUCCESS;
	TERMINAL_ERROR_CODE		tmp;

	if (!stream.is_open())
		return (TERMINAL_ERROR_CODE::BAD_ARGUMENTS);
	while (std::getline(stream, line))
	{
		if ((tmp = ProcessCommand(line)) != TERMINAL_ERROR_CODE::SUCCESS && tmp != TERMINAL_ERROR_CODE::EMPTY_COMMAND)
			success = tmp;
	}
	return (success);
}

}


