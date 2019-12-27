#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow) :
mEventHandler(tWindow),
terrain(500, 500),
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
	mTerminal.LoadGUI(tWindow, &mResourceManager, &mEventHandler);
}

GameState::~GameState()
{

}

void				GameState::update()
{
	if (mTerminalActive)
		mTerminal.UpdateGUI();
	mWindow->update();
	mCamera.Update();
	mPlayer.Update();
	if (mEventHandler.GetActionState(mf::ACTION::TOGGLE_CONSOLE))
	{
		if (mTerminalToggleReset)
		{
			mTerminal.ClearInputGUI();
			mTerminalActive = !mTerminalActive;
			mTerminalToggleReset = false;
		}
	}
	else
		mTerminalToggleReset = true;
	
}

void				GameState::handle_events()
{
	if (mEventHandler.GetActionState(mf::ACTION::QUIT))
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
		scale = glm::scale(scale, glm::vec3(30, 3, 30));
		shader->SetMat4("transform", scale);
		shader->SetMat4("view", mCamera.GetViewMatrix());
		shader->SetMat4("projection", mCamera.GetProjectionMatrix());
	}
	terrain.Draw(GL_TRIANGLES);

	if (mTerminalActive)
	{
		mWindow->pushGLStates();
		glBindBuffer(GL_ARRAY_BUFFER,0);
    	glDisableVertexArrayAttribEXT(0,0);
		mWindow->resetGLStates();
		mTerminal.RenderGUI();
		mWindow->popGLStates();
	}
	mWindow->display();
}
