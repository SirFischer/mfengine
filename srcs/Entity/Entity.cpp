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

} // namespace mf
