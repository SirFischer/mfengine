#pragma once

#include <SFML/Graphics.hpp>
#include <GL/glew.h>


namespace mf
{

class Mesh
{
protected:
	float			*mVertices = NULL;
	unsigned int	*mIndices = NULL;
	GLuint			mVerticeSize;
	GLuint			mIndiceSize;
	GLuint			mVAO, mVBO, mEBO;

void				initMesh();

public:
	Mesh(float *vertices, unsigned int *indices, GLuint verticesize, GLuint indicesize);
	~Mesh();

	void			Bind();

	void			Draw();
};

}
