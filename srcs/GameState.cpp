#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow):
mesh(vertex, NULL, sizeof(vertex), 0)
{
	mWindow = tWindow;
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
	mSpectatorCamera.Update(glm::vec3(cos(range), 0, 2 + sin(range)), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
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
	mf::Shader *shader = mResourceManager.GetShader("helloworld");
	if (shader)
	{
		shader->Bind();
		shader->SetMat4("view", mSpectatorCamera.GetViewMatrix());
		shader->SetMat4("projection", mSpectatorCamera.GetProjectionMatrix());
	}
	mesh.Draw();
	mWindow->display();
}
