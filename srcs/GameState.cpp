#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow)
{
	mWindow = tWindow;
	mResourceManager.LoadShader("helloworld", "assets/shaders/vertex/helloworld.glsl", "assets/shaders/fragment/helloworld.glsl");
	mResourceManager.BindShader("helloworld");
}

GameState::~GameState()
{
	mResourceManager.BindShader("NULL");
}

GameState::ReturnCtrl	GameState::run()
{
	sf::Time	elapsedTime;

	mRunning = true;
	elapsedTime = sf::seconds(DELTATIME);
	while (mRunning && mWindow->isOpen())
	{
		while (elapsedTime.asSeconds() > DELTATIME)
		{
			handle_events();
			update();
			elapsedTime -= sf::seconds(DELTATIME);
		}
		render();
		elapsedTime += mGameLoop.restart();
	}
	return (mReturn);
}

void				GameState::update()
{
	mWindow->update();
}

void				GameState::handle_events()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		mRunning = false;
}

void				GameState::render()
{
	static float i = 0;
	mWindow->clear();

	glPointSize((sin(((float)(i) * 3.1415) / 180.0) + 1) * 100);

	i += 0.01;

	glDrawArrays(GL_POINTS, 0, 1);

	mWindow->display();
}
