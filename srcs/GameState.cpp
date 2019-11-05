#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow) :
terrain(10, 10)
{
	mWindow = tWindow;
	terrain.Randomize(0, -150, 150);
	mResourceManager.LoadShader("helloworld", "assets/shaders/vertex/helloworld.glsl", "assets/shaders/fragment/helloworld.glsl");
}

GameState::~GameState()
{
}


void				GameState::update()
{
	static float range = 0;
	mWindow->update();
	range += 0.02;
	mSpectatorCamera.Update(glm::vec3(0, 3.0 + (sin(range) * 1.0), 8.0), glm::vec3(0, 0.5, 1), glm::vec3(0, 1, 0));
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
		shader->SetMat4("view", mSpectatorCamera.GetViewMatrix());
		shader->SetMat4("projection", mSpectatorCamera.GetProjectionMatrix());
	}
	terrain.Draw();
	mWindow->display();
}
