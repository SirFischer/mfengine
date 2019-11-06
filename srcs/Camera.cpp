#include "Camera.hpp"

namespace mf
{
	
Camera::Camera(/* args */)
{
	GenViewMatrix();
	GenProjectionMatrix();
}

Camera::~Camera()
{

}

void		Camera::GenViewMatrix()
{
	mViewMatrix = glm::lookAt(mPos, mPos - mDir, mUp);
}

void		Camera::GenProjectionMatrix()
{
	mProjectionMatrix = glm::perspective(mFOV, mRatio, mNear, mFar);
}

void		Camera::Update()
{
	if (mEntityAnchor)
	{
		mPos = mEntityAnchor->GetPosition();
		mDir = mEntityAnchor->GetDirection();
	}
	GenViewMatrix();
}

void		Camera::Update(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
	mPos = pos;
	mDir = dir;
	mUp = up;
	GenViewMatrix();
}

void		Camera::SetFov(float fov)
{
	mFOV = fov;
	GenProjectionMatrix();
}

void		Camera::SetScreenDimensions(float ratio)
{
	mRatio = ratio;
	GenProjectionMatrix();
}

void		Camera::SetScreenDimensions(float width, float height)
{
	mRatio = width / height;
	GenProjectionMatrix();
}

void		Camera::SetEntityAnchor(Entity *tEntity)
{
	mEntityAnchor = tEntity;
}

}
