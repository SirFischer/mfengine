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
		MoveForward();
	if (mEventHandler->GetActionState(ACTION::MOVE_RIGHT))
		MoveRight();
	if (mEventHandler->GetActionState(ACTION::MOVE_LEFT))
		MoveLeft();
	if (mEventHandler->GetActionState(ACTION::MOVE_BACKWARD))
		MoveBackward();
}

} // namespace mf
