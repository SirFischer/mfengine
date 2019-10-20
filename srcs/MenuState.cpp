#include "MenuState.hpp"

MenuState::MenuState(Window *tWindow)
{
	mWindow = tWindow;
	mTestButton = new MFGUI::Button(tWindow);
}

MenuState::~MenuState()
{
}

MenuState::ReturnCtrl	MenuState::run()
{
	sf::Time	elapsedTime;

	mRunning = true;
	elapsedTime = sf::seconds(MENUDELTATIME);
	while (mRunning  && mWindow->isOpen())
	{
		while (elapsedTime.asSeconds() > MENUDELTATIME)
		{
			handle_events();
			update();
			elapsedTime -= sf::seconds(MENUDELTATIME);
		}
		render();
		elapsedTime += mGameLoop.restart();
	}
	return (mReturn);
}

void				MenuState::update()
{
	mWindow->update();
	mTestButton->Update();
}

void				MenuState::handle_events()
{
	
}

void				MenuState::render()
{
	mWindow->clear(sf::Color::Green);

	mTestButton->Draw();

	mWindow->display();
}