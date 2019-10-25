#include "MenuState.hpp"

MenuState::MenuState(Window *tWindow)
{
	mWindow = tWindow;
	mTestButton[0] = new mf::Button(tWindow, &mResourceManager);
	mTestButton[0]->SetPosition(sf::Vector2f(100, 100));
	mTestButton[0]->SetScale(sf::Vector2f(4, 3));
	mTestButton[1] = new mf::Button(tWindow, &mResourceManager);
	mTestButton[1]->SetPosition(sf::Vector2f(100, 200));
	mTestButton[1]->SetScale(sf::Vector2f(4, 3));
	mTestButton[2] = new mf::Button(tWindow, &mResourceManager);
	mTestButton[2]->SetPosition(sf::Vector2f(100, 300));
	mTestButton[2]->SetScale(sf::Vector2f(4, 3));
	mTestButton[3] = new mf::Button(tWindow, &mResourceManager);
	mTestButton[3]->SetPosition(sf::Vector2f(100, 400));
	mTestButton[3]->SetScale(sf::Vector2f(4, 3));
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
	mTestButton[0]->Update();
	mTestButton[1]->Update();
	mTestButton[2]->Update();
	mTestButton[3]->Update();
}

void				MenuState::handle_events()
{
	
}

void				MenuState::render()
{
	mWindow->clear(sf::Color::Green);

	mTestButton[0]->Draw();
	mTestButton[1]->Draw();
	mTestButton[2]->Draw();
	mTestButton[3]->Draw();

	mWindow->display();
}