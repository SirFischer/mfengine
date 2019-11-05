#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mf
{

class Camera
{
private:
	glm::vec3	mPos = glm::vec3(0.f, 0.f, 2.f);
	glm::vec3	mDir = glm::vec3(0.f, 0.f, 1.f);
	glm::vec3	mUp = glm::vec3(0.f, 1.f, 0.f);
	glm::mat4	mViewMatrix;
	glm::mat4	mProjectionMatrix;

	float		mFOV = 70;
	float		mRatio = 16.0f/9.0f;
	float		mNear = 0.1f;
	float		mFar = 100.0f;

	void		GenViewMatrix();
	void		GenProjectionMatrix();

public:
	Camera();
	~Camera();

	void		Update(glm::vec3 pos, glm::vec3 dir, glm::vec3 up);

	void		SetFov(float fov);
	void		SetScreenDimensions(float ratio);
	void		SetScreenDimensions(float width, float height);

	glm::mat4	GetViewMatrix() {return mViewMatrix;}
	glm::mat4	GetProjectionMatrix() {return mProjectionMatrix;}
};

}
