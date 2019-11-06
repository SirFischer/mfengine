#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow) :
terrain(200, 200)
{
	mWindow = tWindow;
	//terrain.Randomize(0, -10, 10);
	terrain.GenHeightMap(time(0));
	mResourceManager.LoadShader("helloworld", "assets/shaders/vertex/helloworld.glsl", "assets/shaders/fragment/helloworld.glsl");
}

GameState::~GameState()
{
}


void				GameState::update()
{
	mWindow->update();
	mCamera.Update();
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
	mf::Shader *shader = mResourceManager.GetShader("helloworld");
	if (shader)
	{
		shader->Bind();
		shader->SetMat4("view", mCamera.GetViewMatrix());
		shader->SetMat4("projection", mCamera.GetProjectionMatrix());
	}
	terrain.Draw();
	mWindow->display();
}
