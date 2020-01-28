#include "Mesh.hpp"

namespace mf
{

Mesh::Mesh(float *vertices, unsigned int *indices, GLuint verticesize, GLuint indicesize) :
mVertices(vertices),
mIndices(indices)
{
	mVerticeSize = verticesize;
	mIndiceSize = indicesize;
	initMesh();
}

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void		Mesh::initMesh()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVerticeSize, mVertices.get(), GL_STATIC_DRAW);
	if (mIndices)
	{
		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndiceSize, mIndices.get(), GL_STATIC_DRAW);
	}
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	if (mTextureCoords)
	{
		glGenBuffers(1, &mTBO);
		glBindBuffer(GL_ARRAY_BUFFER, mTBO);
		glBufferData(GL_ARRAY_BUFFER, mTextureCoordsSize, mTextureCoords.get(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	}
}

void		Mesh::Bind()
{
	glBindVertexArray(mVAO);
}

void		Mesh::Draw()
{
	Draw(GL_TRIANGLES);
}

void		Mesh::Draw(GLenum mode)
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture);
	if (mShader)
	{
		mShader->Bind();
		mShader->SetMat4("transform", mTransform);
		mShader->SetMat4("view", mView);
		mShader->SetMat4("projection", mProjection);
		mShader->SetInt("texture1", 0);
	}
	glBindVertexArray(mVAO);
	if (mIndices)
		glDrawElements(mode, mIndiceSize, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, mVerticeSize / 3);
	glBindVertexArray(0);
}

void		Mesh::SetTransformMatrix(glm::mat4 mat)
{
	mTransform = mat;
}

void		Mesh::SetViewMatrix(glm::mat4 mat)
{
	mView = mat;
}

void		Mesh::SetProjectionMatrix(glm::mat4 mat)
{
	mProjection = mat;
}

void		Mesh::SetShaderProgram(mf::Shader *shader)
{
	mShader = shader;
}

void		Mesh::SetTexture(sf::Image tImage)
{
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_2D, mTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tImage.getSize().x,tImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tImage.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);
}

}
