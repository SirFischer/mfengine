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
	static float x = 0;

	mWindow->clear();

	x += 0.01;
	mResourceManager.GetShader("helloworld")->setUniform("rel", (float)(sin((x / 180.0) * 3.1416)));
	glDrawArrays(GL_TRIANGLES, 0, 3);

	mWindow->display();
}
