#include "GameState.hpp"

GameState::GameState(mf::Window *tWindow) :
mEventHandler(tWindow),
mWorld(&mResourceManager, &mCamera),
mPlayer(&mEventHandler),
mFPSDisplay(tWindow, &mResourceManager, &mEventHandler)
{
	mWindow = tWindow;
	mPlayer.SetCamera(&mCamera);
	mEventHandler.SetCursorLock(true);
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
	else
		mPlayer.Update();
	mWindow->update();
	mCamera.Update();
	mWorld.Update(mCamera.GetViewMatrix());
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
	mWorld.Draw(&mRenderer);
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
