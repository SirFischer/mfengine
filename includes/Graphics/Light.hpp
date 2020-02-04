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
		float		mSpecularStrength = 0.25;
		int			mSpecularPower = 64;
		
	public:
		Light(/* args */);
		~Light();

		void		SetPosition(glm::vec3 tPosition) {mPosition = tPosition;}
		void		SetAmbientLight(glm::vec3 tAmbient) {mAmbient = tAmbient;}
		void		SetDiffuseLight(glm::vec3 tDiffuse) {mDiffuse = tDiffuse;}
		void		SetSpecularLight(glm::vec3 tSpecular) {mSpecular = tSpecular;}

		glm::vec3	GetPosition() {return (mPosition);}
		glm::vec3	GetAmbientLight() {return (mAmbient);}
		glm::vec3	GetDiffuseLight() {return (mDiffuse);}
		glm::vec3	GetSpecularLight() {return (mSpecular);}
		float		GetSpecularStrength() {return (mSpecularStrength);}
		int			GetSpecularPower() {return (mSpecularPower);}
	};
}

