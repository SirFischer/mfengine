#include "Entity.hpp"

namespace mf
{

Entity::Entity()
{
}

Entity::~Entity()
{
}

void		Entity::MoveForward()
{
	glm::vec3		dir = glm::vec3(mDir[0] * mAcceleration, 0, mDir[2] * mAcceleration);

	mVelocity -= dir;
}

void		Entity::MoveLeft()
{
	glm::vec3		dir = glm::vec3(mDir[0] * mAcceleration, 0, mDir[2] * mAcceleration);

	dir = glm::cross(dir, glm::vec3(0, 1, 0));
	mVelocity += dir;
}

void		Entity::MoveRight()
{
	glm::vec3		dir = glm::vec3(mDir[0] * mAcceleration, 0, mDir[2] * mAcceleration);

	dir = glm::cross(dir, glm::vec3(0, 1, 0));
	mVelocity -= dir;
}

void		Entity::MoveBackward()
{
	glm::vec3		dir = glm::vec3(mDir[0] * mAcceleration, 0, mDir[2] * mAcceleration);

	mVelocity += dir;
}

void		Entity::MoveUp()
{
	mVelocity.y += mAcceleration;
}

void		Entity::MoveDown()
{
	mVelocity.y -= mAcceleration;
}

void		Entity::MoveJump()
{
	if (mOnGround)
		mVelocity.y += mAcceleration * 15;
}

void		Entity::SetCamera(Camera *tCamera)
{
	mCamera = (tCamera);
}

void		Entity::HandleTerrainCollision(mf::Terrain *terrain)
{
	if (!mOnGround)
		mVelocity.y -= 0.010f;
	mOnGround = false;
	float terrainHeight = terrain->GetHeightInWorld(mPos.x, mPos.z);
	if (mPos.y - mHeight - 0.1 < terrainHeight)
	{
		mOnGround = true;
		mPos.y = terrainHeight + mHeight;
		mVelocity.y = 0;
	}
}

} // namespace mf
