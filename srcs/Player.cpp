#include "Player.hpp"

namespace mf
{

Player::Player(EventHandler *tEventHandler)
{
	mEventHandler = tEventHandler;
}

Player::~Player()
{
}

void		Player::Update()
{
	mPos += mVelocity;
}

void		Player::HandleEvents()
{
	if (mEventHandler->GetActionState(ACTION::MOVE_FORWARD))
	{
		mPos -= mDir; // * speed
	}
	if (mEventHandler->GetActionState(ACTION::MOVE_BACKWARD))
	{
		mPos += mDir; // * speed
	}
}

} // namespace mf
