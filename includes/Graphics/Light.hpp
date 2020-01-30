#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace mf
{
	class Light
	{
	private:
		glm::vec3	mPosition;

		glm::vec3	mAmbient;
		glm::vec3	mDiffuse;
		glm::vec3	mSpecular;
	public:
		Light(/* args */);
		~Light();
	};
}

