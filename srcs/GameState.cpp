#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow) :
mEventHandler(tWindow),
terrain(1000, 1000),
mPlayer(&mEventHandler)
{
	mWindow = tWindow;
	//terrain.Randomize(0, -10, 10);
	mCamera.SetEntityAnchor(&mPlayer);
	terrain.GenHeightMap(time(0));
	mResourceManager.LoadShader("helloworld", "assets/shaders/vertex/helloworld.glsl", "assets/shaders/fragment/helloworld.glsl");
	mTerminal.mEventHandler = &mEventHandler;
	if (std::experimental::filesystem::exists("assets/cfg/controls.cfg"))
		mTerminal.ReadFromFile("assets/cfg/controls.cfg");
	else
		mTerminal.ReadFromFile("assets/cfg/controls_default.cfg");
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
		glm::mat4	scale = glm::mat4(1.0);
		scale = glm::scale(scale, glm::vec3(3, 1, 3));
		shader->SetMat4("transform", scale);
		shader->SetMat4("view", mCamera.GetViewMatrix());
		shader->SetMat4("projection", mCamera.GetProjectionMatrix());
	}
	terrain.Draw(GL_TRIANGLES);
	mWindow->display();
}
