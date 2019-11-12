#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow) :
mEventHandler(tWindow),
terrain(200, 200),
mPlayer(&mEventHandler)
{
	mWindow = tWindow;
	//terrain.Randomize(0, -10, 10);
	mCamera.SetEntityAnchor(&mPlayer);
	terrain.GenHeightMap(time(0));
	mResourceManager.LoadShader("helloworld", "assets/shaders/vertex/helloworld.glsl", "assets/shaders/fragment/helloworld.glsl");

	mEventHandler.BindKey(sf::Keyboard::W, mf::ACTION::MOVE_FORWARD);
	mEventHandler.BindKey(sf::Keyboard::S, mf::ACTION::MOVE_BACKWARD);
}

GameState::~GameState()
{

}


void				GameState::update()
{
	mWindow->update();
	mCamera.Update();
	mPlayer.Update();
}

void				GameState::handle_events()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		mRunning = false;
	mEventHandler.HandleEvents();
	mPlayer.HandleEvents();
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
