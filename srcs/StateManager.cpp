#include "StateManager.hpp"

StateManager::StateManager(Window *tWindow):
mWindow(tWindow)
{

}

StateManager::~StateManager()
{
}

void		StateManager::state_push(ScreenState *state)
{
	mStates.push(state);
}

void		StateManager::state_pop()
{
	ScreenState	*state = mStates.top();
	mStates.pop();
	delete state;
}

void		StateManager::run()
{
	while (mStates.size())
	{
		switch (mStates.top()->run())
		{
		case ScreenState::ReturnCtrl::END:
			state_pop();
			break;
		case ScreenState::ReturnCtrl::GAME:
			mStates.push(new GameState(mWindow));
			break;
		default:
			state_pop();
			break;
		}
	}
}