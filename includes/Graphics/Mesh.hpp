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
	std::shared_ptr<unsigned int>	mIndices;
	GLuint							mVerticeSize;
	GLuint							mIndiceSize;
	GLuint							mVAO, mVBO, mEBO;

	mf::Shader						*mShader = NULL;
	glm::mat4						mTransform = glm::mat4(1.0);
	glm::mat4						mView = glm::mat4(1.0);
	glm::mat4						mProjection = glm::mat4(1.0);

void				initMesh();

public:
					Mesh(float *vertices, unsigned int *indices, GLuint verticesize, GLuint indicesize);
					Mesh();
					~Mesh();

	void			Bind();

	void			Draw();
	void			Draw(GLenum mode);

	void			SetTransformMatrix(glm::mat4 mat);
	void			SetViewMatrix(glm::mat4 mat);
	void			SetProjectionMatrix(glm::mat4 mat);
	void			SetShaderProgram(mf::Shader *shader);
};

}
