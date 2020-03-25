#include "Mesh.hpp"

namespace mf
{

Mesh::Mesh(float *vertices, unsigned int *indices, GLuint verticesize, GLuint indicesize)
{
	try
	{
		mVertices = std::shared_ptr<float>(new float[verticesize / sizeof(float)]);
		if (indicesize)
			mIndices = std::shared_ptr<unsigned int>(new unsigned int[indicesize  / sizeof(unsigned int)]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::memmove(mVertices.get(), vertices, verticesize);
	std::memmove(mIndices.get(), indices, indicesize);
	mVerticeSize = verticesize;
	mIndiceSize = indicesize;
	initMesh();
}

Mesh::Mesh(float *vertices, unsigned int *indices, float *textureCoords, GLuint verticesize, GLuint indicesize, GLuint textureCoordsSize)
{
	try
	{
		mVertices = std::shared_ptr<float>(new float[verticesize / sizeof(float)]);
		if (indicesize)
			mIndices = std::shared_ptr<unsigned int>(new unsigned int[indicesize  / sizeof(unsigned int)]);
		if (textureCoordsSize)
			mTextureCoords = std::shared_ptr<float>(new float[textureCoordsSize / sizeof(float)]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::memmove(mVertices.get(), vertices, verticesize);
	std::memmove(mIndices.get(), indices, indicesize);
	std::memmove(mTextureCoords.get(), textureCoords, textureCoordsSize);
	mVerticeSize = verticesize;
	mIndiceSize = indicesize;
	mTextureCoordsSize = textureCoordsSize;
	initMesh();
}

Mesh::Mesh(float *vertices, unsigned int *indices, float *textureCoords, float *normals, GLuint verticesize, GLuint indicesize, GLuint textureCoordsSize, GLuint normalsize)
{
	try
	{
		mVertices = std::shared_ptr<float>(new float[verticesize / sizeof(float)]);
		if (indicesize)
			mIndices = std::shared_ptr<unsigned int>(new unsigned int[indicesize  / sizeof(unsigned int)]);
		if (textureCoordsSize)
			mTextureCoords = std::shared_ptr<float>(new float[textureCoordsSize / sizeof(float)]);
		if (normalsize)
			mNormals = std::shared_ptr<float>(new float[normalsize / sizeof(float)]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::memmove(mVertices.get(), vertices, verticesize);
	std::memmove(mIndices.get(), indices, indicesize);
	std::memmove(mTextureCoords.get(), textureCoords, textureCoordsSize);
	std::memmove(mNormals.get(), normals, normalsize);
	mVerticeSize = verticesize;
	mIndiceSize = indicesize;
	mTextureCoordsSize = textureCoordsSize;
	mNormalSize = normalsize;
	initMesh();
}

Mesh::Mesh(const Mesh &tMesh)
{
	try
	{
		mVertices = std::shared_ptr<float>(new float[tMesh.mVerticeSize / sizeof(float)]);
		if (tMesh.mIndiceSize)
			mIndices = std::shared_ptr<unsigned int>(new unsigned int[tMesh.mIndiceSize  / sizeof(unsigned int)]);
		if (tMesh.mTextureCoordsSize)
			mTextureCoords = std::shared_ptr<float>(new float[tMesh.mTextureCoordsSize / sizeof(float)]);
		if (tMesh.mNormalSize)
			mNormals = std::shared_ptr<float>(new float[tMesh.mNormalSize / sizeof(float)]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::memmove(mVertices.get(), tMesh.mVertices.get(), tMesh.mVerticeSize);
	std::memmove(mIndices.get(), tMesh.mIndices.get(), tMesh.mIndiceSize);
	std::memmove(mTextureCoords.get(), tMesh.mTextureCoords.get(), tMesh.mTextureCoordsSize);
	std::memmove(mNormals.get(), tMesh.mNormals.get(), tMesh.mNormalSize);
	mVerticeSize = tMesh.mVerticeSize;
	mIndiceSize = tMesh.mIndiceSize;
	mTextureCoordsSize = tMesh.mTextureCoordsSize;
	mNormalSize = tMesh.mNormalSize;
	mShader = tMesh.mShader;
	mTransform = tMesh.mTransform;
	mProjection = tMesh.mProjection;
	mMaterial = tMesh.mMaterial;
	mTexture = tMesh.mTexture;
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
	if (mNormals)
	{
		glGenBuffers(1, &mNBO);
		glBindBuffer(GL_ARRAY_BUFFER, mNBO);
		glBufferData(GL_ARRAY_BUFFER, mVerticeSize, mNormals.get(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	}
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

void		Mesh::PrepareShader()
{
	glDepthFunc(mDepthFunc);
	glBindVertexArray(mVAO);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(mTextureType, mTexture);
	if (mShader)
	{
		mShader->Bind();
		mShader->SetMat4("transform", mTransform);
		mShader->SetMat4("view", mView);
		mShader->SetMat4("projection", mProjection);
		mShader->SetVec3("material.ambient", mMaterial.ambient);
		mShader->SetVec3("material.diffuse", mMaterial.diffuse);
		mShader->SetVec3("material.specular", mMaterial.specular);
		mShader->SetFloat("material.shininess", mMaterial.shininess);
		if (mTexture > 0)
			mShader->SetInt("hasTexture", 1);
		else
			mShader->SetInt("hasTexture", 0);
		mShader->SetInt("texture1", 0);
	}
}

void		Mesh::Draw()
{
	Draw(GL_TRIANGLES);
}

void		Mesh::Draw(GLenum mode)
{
	glBindVertexArray(mVAO);
	if (mIndices)
		glDrawElements(mode, mIndiceSize, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(mode, 0, mVerticeSize / 3);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tImage.getSize().x,tImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tImage.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void		Mesh::SetCubeMap(sf::Image tFront, sf::Image tBack, sf::Image tLeft, sf::Image tRight, sf::Image tUp, sf::Image tDown)
{
	glGenTextures(1, &mTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, GL_RGB, tFront.getSize().x, tFront.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, tFront.getPixelsPtr());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, GL_RGB, tBack.getSize().x, tBack.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, tBack.getPixelsPtr());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, GL_RGB, tLeft.getSize().x, tLeft.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, tLeft.getPixelsPtr());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, GL_RGB, tRight.getSize().x, tRight.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, tRight.getPixelsPtr());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, GL_RGB, tUp.getSize().x, tUp.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, tUp.getPixelsPtr());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, GL_RGB, tDown.getSize().x, tDown.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, tDown.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

}
