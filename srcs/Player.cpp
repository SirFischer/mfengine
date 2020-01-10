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
	if (mCamera)
	{
		mCamera->UpdateFront(mEventHandler);
		mDir = mCamera->GetDir();
		mCamera->SetPos(mPos);
	}
}

void		Player::HandleEvents()
{
	std::clamp(mDir.y, -1.f, 1.f);
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
