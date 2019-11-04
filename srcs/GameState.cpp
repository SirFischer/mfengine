#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow):
mesh(vertex, NULL, sizeof(vertex), 0)
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
	mWindow->clear();
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	mesh.Draw();
	mWindow->display();
}
