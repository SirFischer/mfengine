#include "MenuState.hpp"

MenuState::MenuState(mf::Window *tWindow):
mContainer(tWindow),
mPlayButton(tWindow, &mResourceManager),
mOptionsButton(tWindow, &mResourceManager),
mQuitButton(tWindow, &mResourceManager),
mContainerOptions(tWindow),
mFullScreenButton(tWindow, &mResourceManager),
mBackButton(tWindow, &mResourceManager)
{
	mWindow = tWindow;
	mState = MENU_STATE::MAIN;
	mReturn = ReturnCtrl::END;
	mRunning = true;
	initMenuButtons();
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

	switch (mState)
	{
	case MENU_STATE::MAIN:
		mContainer.Update();
		updateMain();
		break;
	case MENU_STATE::OPTIONS:
		mContainerOptions.Update();
		updateOptions();
		break;
	default:
		mContainer.Update();
		updateMain();
		break;
	}
}

void			MenuState::updateMain()
{
	if (mQuitButton.GetState() == mf::MouseState::CLICKED)
	{
		mReturn = ReturnCtrl::END;
		mRunning = false;
	}
	if (mPlayButton.GetState() == mf::MouseState::CLICKED)
	{
		mReturn = ReturnCtrl::GAME;
		mRunning = false;
	}
	if (mOptionsButton.GetState() == mf::MouseState::CLICKED)
	{
		mState = MENU_STATE::OPTIONS;
	}
}

void			MenuState::updateOptions()
{
	if (mFullScreenButton.GetState() == mf::MouseState::CLICKED)
	{
		mWindow->toggleFullscreen();
		mFullScreenButton.SetText((mWindow->isFullscreen()) ? "Windowed" : "Fullscreen");
	}
	if (mBackButton.GetState() == mf::MouseState::CLICKED)
		mState = MENU_STATE::MAIN;
}

void				MenuState::handle_events()
{
	
}

void				MenuState::render()
{
	mWindow->clear(sf::Color::Green);

	switch (mState)
	{
	case MENU_STATE::MAIN:
		mContainer.Draw();
		break;
	case MENU_STATE::OPTIONS:
		mContainerOptions.Draw();
		break;
	default:
		mContainer.Draw();
		break;
	}
	
	mWindow->display();
}

void				MenuState::initMenuButtons()
{
	//MAIN
	mPlayButton.SetPosition(sf::Vector2f(850, 400));
	mPlayButton.SetScale(sf::Vector2f(8, 5));
	mPlayButton.SetFont("assets/fonts/pdark.ttf");
	mPlayButton.SetText("PLAY");
	mPlayButton.SetTextOffset(sf::Vector2f(50, 20));
	mContainer.AddItem(&mPlayButton);
	mOptionsButton.SetPosition(sf::Vector2f(850, 500));
	mOptionsButton.SetScale(sf::Vector2f(8, 5));
	mOptionsButton.SetFont("assets/fonts/pdark.ttf");
	mOptionsButton.SetText("Options");
	mOptionsButton.SetTextOffset(sf::Vector2f(30, 20));
	mContainer.AddItem(&mOptionsButton);
	mQuitButton.SetPosition(sf::Vector2f(850, 600));
	mQuitButton.SetScale(sf::Vector2f(8, 5));
	mQuitButton.SetFont("assets/fonts/pdark.ttf");
	mQuitButton.SetText("QUIT");
	mQuitButton.SetTextOffset(sf::Vector2f(50, 20));
	mContainer.AddItem(&mQuitButton);

	//OPTIONS
	mFullScreenButton.SetPosition(sf::Vector2f(850, 400));
	mFullScreenButton.SetScale(sf::Vector2f(8, 5));
	mFullScreenButton.SetFont("assets/fonts/pdark.ttf");
	mFullScreenButton.SetText("Fullscreen");
	mFullScreenButton.SetTextOffset(sf::Vector2f(50, 20));
	mFullScreenButton.SetTextSize(20);
	mContainerOptions.AddItem(&mFullScreenButton);
	mBackButton.SetPosition(sf::Vector2f(250, 100));
	mBackButton.SetScale(sf::Vector2f(8, 5));
	mBackButton.SetFont("assets/fonts/pdark.ttf");
	mBackButton.SetText("Back");
	mBackButton.SetTextOffset(sf::Vector2f(50, 20));
	mBackButton.SetTextSize(20);
	mContainerOptions.AddItem(&mBackButton);
}