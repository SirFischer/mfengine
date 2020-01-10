#include "EventHandler.hpp"

namespace mf
{

EventHandler::EventHandler(Window *tWindow)
{
	mWindow = tWindow;
}

EventHandler::~EventHandler()
{
	
}

void	EventHandler::HandleEvents()
{
	sf::Event	event;

	mTextInputString = "";
	while (mWindow->pollEvent(event))
	{
		if (event.type == event.TextEntered)
			mTextInputString += event.text.unicode;
		if ( event.type == sf::Event::KeyPressed)
		{
			if (mKeyMap.find(event.key.code) != mKeyMap.end())
			{
				mKeyStateMap[event.key.code] = true;
				mActionMap[mKeyMap[event.key.code]] = true;
			}
		}
		if ( event.type == sf::Event::KeyReleased)
		{
			if (mKeyMap.find(event.key.code) != mKeyMap.end())
			{
				mKeyStateMap[event.key.code] = false;
				mActionMap[mKeyMap[event.key.code]] = false;
			}
			
		}
	}
	
	mMousePosOffset = sf::Mouse::getPosition() - mLastMousePos;
	if (mCursorIsGrabbed)
		mWindow->setRelMousePos(sf::Vector2i(mWindow->getSize().x / 2, mWindow->getSize().y / 2));
	mLastMousePos = sf::Mouse::getPosition();
}

bool		EventHandler::GetKeyState(int key)
{
	return (mKeyStateMap[key]);
}

bool		EventHandler::GetSubActionState(ACTION action)
{
	return (mSubActionMap[action]);
}

bool		EventHandler::GetActionState(ACTION action)
{
	return (mActionMap[action]);
}

void		EventHandler::BindKey(int key, ACTION action)
{
	mKeyMap[key] = action;
}

void		EventHandler::UnbindAllKeys()
{
	mKeyMap.clear();
}

void		EventHandler::ToggleAction(ACTION action, bool state)
{
	mActionMap[action] = state;
}

} // namespace mf
