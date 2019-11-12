#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

namespace mf
{

class Entity
{
protected:
	glm::vec3		mPos = glm::vec3(0, 0, 0);
	glm::vec3		mDir = glm::vec3(0, 0, 1);
	glm::vec3		mVelocity;
	double			mMaxSpeed;

public:
	Entity();
	~Entity();

	virtual void	Update() = 0;
	virtual void	HandleEvents() = 0;

	glm::vec3		GetPosition(){return (mPos);}
	glm::vec3		GetDirection(){return (mDir);}
};

} // namespace mf
