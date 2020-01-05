#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <memory>
#include <GL/glew.h>


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

void				initMesh();

public:
	Mesh(float *vertices, unsigned int *indices, GLuint verticesize, GLuint indicesize);
	Mesh();
	~Mesh();

	void			Bind();

	void			Draw();
	void			Draw(GLenum mode);
};

}
