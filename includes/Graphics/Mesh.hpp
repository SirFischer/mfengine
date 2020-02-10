#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.hpp"


namespace mf
{

class Mesh
{
protected:
	std::shared_ptr<float>			mVertices;
	std::shared_ptr<float>			mNormals;
	std::shared_ptr<float>			mTextureCoords;
	std::shared_ptr<unsigned int>	mIndices;
	GLuint							mVerticeSize = 0;
	GLuint							mNormalSize = 0;
	GLuint							mTexture;
	GLuint							mTextureType = GL_TEXTURE_2D;
	GLuint							mDepthFunc = GL_LESS;
	GLuint							mTextureCoordsSize = 0;
	GLuint							mIndiceSize = 0;
	GLuint							mVAO, mVBO, mTBO, mNBO, mEBO;

	mf::Shader						*mShader = NULL;
	glm::mat4						mTransform = glm::mat4(1.0);
	glm::mat4						mView = glm::mat4(1.0);
	glm::mat4						mProjection = glm::mat4(1.0);

	std::string						mName;

	struct							s_material
	{
		glm::vec3					ambient = glm::vec3(0, 0, 0);
		glm::vec3					diffuse = glm::vec3(0.1, 0.1, 0.1);
		glm::vec3					specular = glm::vec3(0.5, 0.5, 0.5);
		float						shininess = 0.25;
	}								mMaterial;

void				initMesh();

public:
					Mesh(float *vertices, unsigned int *indices, GLuint verticesize, GLuint indicesize);
					Mesh(float *vertices, unsigned int *indices, float *textureCoords, GLuint verticesize, GLuint indicesize, GLuint textureCoordsSize);
					Mesh(float *vertices, unsigned int *indices, float *textureCoords, float *normals, GLuint verticesize, GLuint indicesize, GLuint textureCoordsSize, GLuint normalsize);
					Mesh();
					~Mesh();

	void			Bind();

	void			PrepareShader();

	void			Draw();
	void			Draw(GLenum mode);


	void			SetName(std::string tName){mName = tName;}
	void			SetTransformMatrix(glm::mat4 mat);
	void			SetViewMatrix(glm::mat4 mat);
	void			SetProjectionMatrix(glm::mat4 mat);
	void			SetShaderProgram(mf::Shader *shader);

	void			SetDepthFunc(GLuint tDepthFunc) {mDepthFunc = tDepthFunc;}

	void			SetTexture(sf::Image tImage);
	void			SetCubeMap(sf::Image tFront, sf::Image tBack, sf::Image tLeft, sf::Image tRight, sf::Image tUp, sf::Image tDown);

	mf::Shader		*GetShaderProgram() {return (mShader);}
};

}
