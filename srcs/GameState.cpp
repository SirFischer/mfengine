#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow) :
mEventHandler(tWindow),
terrain(500, 500),
mPlayer(&mEventHandler),
mFPSDisplay(tWindow, &mResourceManager, &mEventHandler)
{
	mWindow = tWindow;
	mPlayer.SetCamera(&mCamera);
	terrain.GenHeightMap(time(0));
	mEventHandler.SetCursorLock(true);
	mResourceManager.LoadShader("helloworld", "assets/shaders/vertex/helloworld.glsl", "assets/shaders/fragment/helloworld.glsl");
	mTerminal.mEventHandler = &mEventHandler;
	if (std::experimental::filesystem::exists("assets/cfg/controls.cfg"))
		mTerminal.ReadFromFile("assets/cfg/controls.cfg");
	else
		mTerminal.ReadFromFile("assets/cfg/controls_default.cfg");
	mTerminal.LoadGUI(tWindow, &mResourceManager, &mEventHandler);
	mWindow->setMouseCursorVisible(false);
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
	mFPSDisplay.SetText(std::to_string(mFPS) + " FPS");
	if (mEventHandler.GetActionState(mf::ACTION::TOGGLE_CONSOLE))
	{
		if (mTerminalToggleReset)
		{
			mTerminal.ClearInputGUI();
			mTerminalActive = !mTerminalActive;
			mEventHandler.SetCursorLock(!mTerminalActive);
			mWindow->setMouseCursorVisible(mTerminalActive);
			mTerminalToggleReset = false;
		}
	}
	else
		mTerminalToggleReset = true;
	
}

void				GameState::handle_events()
{
	if (mEventHandler.GetActionState(mf::ACTION::QUIT))
	{
		mRunning = false;
		mWindow->setMouseCursorVisible(true);
	}
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

	mWindow->pushGLStates();
	glBindBuffer(GL_ARRAY_BUFFER,0);
    glDisableVertexArrayAttribEXT(0,0);
	mWindow->resetGLStates();
	if (mTerminalActive)
		mTerminal.RenderGUI();
	mFPSDisplay.Draw();
	mWindow->popGLStates();
	mWindow->display();
}
