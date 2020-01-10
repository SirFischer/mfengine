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
	GenViewMatrix();
}

void		Camera::Update(glm::vec3 pos, glm::vec3 dir, glm::vec3 up)
{
	mPos = pos;
	mDir = dir;
	mUp = up;
	GenViewMatrix();
}

void		Camera::UpdateFront(EventHandler *tEventHandler)
{
	sf::Vector2f	offset = sf::Vector2f(tEventHandler->GetMousePosOffset()) * mMouseSensitivity;
	mYaw += offset.x;
	mPitch += offset.y;
	mPitch = std::clamp(mPitch, -89.f, 89.f);
	mFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront.y = sin(glm::radians(mPitch));
	mFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
	mFront = glm::normalize(mFront);
	mDir = mFront;
}

void		Camera::SetPos(glm::vec3 tPos)
{
	mPos = tPos;
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

}
