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

	while (mWindow->pollEvent(event))
	{
		if ( event.type == sf::Event::KeyPressed)
		{
			if (mKeyMap.find(event.key.code) != mKeyMap.end())
				mActionMap[mKeyMap[event.key.code]] = true;
		}
		if ( event.type == sf::Event::KeyReleased)
		{
			if (mKeyMap.find(event.key.code) != mKeyMap.end())
				mActionMap[mKeyMap[event.key.code]] = false;
		}
	}
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


} // namespace mf