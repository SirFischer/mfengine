#include "Skybox.hpp"

namespace mf
{
	Skybox::Skybox(sf::Image tFront, sf::Image tBack, sf::Image tLeft, sf::Image tRight, sf::Image tUp, sf::Image tDown)
	:mFront(cVertices, NULL, cTexCoords, sizeof(float) * 18, 0, sizeof(float) * 12)
	,mBack(cVertices + (18), NULL, cTexCoords + (12), sizeof(float) * 18, 0, sizeof(float) * 12)
	,mRight(cVertices + (18 * 2), NULL, cTexCoords + (12 * 2), sizeof(float) * 18, 0, sizeof(float) * 12)
	{
		mFront.SetTexture(tFront);
		mBack.SetTexture(tBack);
		mRight.SetTexture(tRight);
		(void)tLeft;
		(void)tUp;
		(void)tDown;
	}
	
	Skybox::~Skybox()
	{
		
	}

	void	Skybox::SetProjectionMatrix(glm::mat4 tMat)
	{
		mFront.SetProjectionMatrix(tMat);
		mBack.SetProjectionMatrix(tMat);
		mRight.SetProjectionMatrix(tMat);
	}

	void	Skybox::SetShaderProgram(mf::Shader *tShader)
	{
		mFront.SetShaderProgram(tShader);
		mBack.SetShaderProgram(tShader);
		mRight.SetShaderProgram(tShader);
	}

	void	Skybox::SetTransformMatrix(glm::mat4 tMat)
	{
		mFront.SetTransformMatrix(tMat);
		mBack.SetTransformMatrix(tMat);
		mRight.SetTransformMatrix(tMat);
	}

	void	Skybox::SetViewMatrix(glm::mat4 tMat)
	{
		mFront.SetViewMatrix(tMat);
		mBack.SetViewMatrix(tMat);
		mRight.SetViewMatrix(tMat);
	}

	void	Skybox::Draw(mf::Renderer *tRenderer)
	{
		tRenderer->AddMesh(&mFront);
		tRenderer->AddMesh(&mBack);
		tRenderer->AddMesh(&mRight);
	}
} // namespace mf
