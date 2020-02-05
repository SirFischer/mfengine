#include "Skybox.hpp"

namespace mf
{
	Skybox::Skybox(sf::Image tFront, sf::Image tBack, sf::Image tLeft, sf::Image tRight, sf::Image tUp, sf::Image tDown)
	:mFront(cVertices, NULL, cTexCoords, sizeof(float) * 18, 0, sizeof(float) * 12)
	,mBack(cVertices + (18), NULL, cTexCoords + (12), sizeof(float) * 18, 0, sizeof(float) * 12)
	,mRight(cVertices + (18 * 2), NULL, cTexCoords + (12 * 2), sizeof(float) * 18, 0, sizeof(float) * 12)
	,mLeft(cVertices + (18 * 3), NULL, cTexCoords + (12 * 3), sizeof(float) * 18, 0, sizeof(float) * 12)
	,mUp(cVertices + (18 * 4), NULL, cTexCoords + (12 * 4), sizeof(float) * 18, 0, sizeof(float) * 12)
	,mDown(cVertices + (18 * 5), NULL, cTexCoords + (12 * 5), sizeof(float) * 18, 0, sizeof(float) * 12)
	{
		mFront.SetTexture(tFront);
		mBack.SetTexture(tBack);
		mRight.SetTexture(tRight);
		mLeft.SetTexture(tLeft);
		mUp.SetTexture(tUp);
		mDown.SetTexture(tDown);

		mFront.SetDepthFunc(GL_LEQUAL);
		mBack.SetDepthFunc(GL_LEQUAL);
		mRight.SetDepthFunc(GL_LEQUAL);
		mLeft.SetDepthFunc(GL_LEQUAL);
		mUp.SetDepthFunc(GL_LEQUAL);
		mDown.SetDepthFunc(GL_LEQUAL);
	}
	
	Skybox::~Skybox()
	{
		
	}

	void	Skybox::SetProjectionMatrix(glm::mat4 tMat)
	{
		mFront.SetProjectionMatrix(tMat);
		mBack.SetProjectionMatrix(tMat);
		mRight.SetProjectionMatrix(tMat);
		mLeft.SetProjectionMatrix(tMat);
		mUp.SetProjectionMatrix(tMat);
		mDown.SetProjectionMatrix(tMat);
	}

	void	Skybox::SetShaderProgram(mf::Shader *tShader)
	{
		mFront.SetShaderProgram(tShader);
		mBack.SetShaderProgram(tShader);
		mRight.SetShaderProgram(tShader);
		mLeft.SetShaderProgram(tShader);
		mUp.SetShaderProgram(tShader);
		mDown.SetShaderProgram(tShader);
	}

	void	Skybox::SetTransformMatrix(glm::mat4 tMat)
	{
		mFront.SetTransformMatrix(tMat);
		mBack.SetTransformMatrix(tMat);
		mRight.SetTransformMatrix(tMat);
		mLeft.SetTransformMatrix(tMat);
		mUp.SetTransformMatrix(tMat);
		mDown.SetTransformMatrix(tMat);
	}

	void	Skybox::SetViewMatrix(glm::mat4 tMat)
	{
		mFront.SetViewMatrix(tMat);
		mBack.SetViewMatrix(tMat);
		mRight.SetViewMatrix(tMat);
		mLeft.SetViewMatrix(tMat);
		mUp.SetViewMatrix(tMat);
		mDown.SetViewMatrix(tMat);
	}

	void	Skybox::Draw(mf::Renderer *tRenderer)
	{
		tRenderer->AddMesh(&mFront);
		tRenderer->AddMesh(&mBack);
		tRenderer->AddMesh(&mRight);
		tRenderer->AddMesh(&mLeft);
		tRenderer->AddMesh(&mUp);
		tRenderer->AddMesh(&mDown);
	}
} // namespace mf
