#include "Mesh.hpp"

namespace mf
{

Mesh::Mesh(float *vertices, unsigned int *indices, GLuint verticesize, GLuint indicesize)
{
	mVertices = vertices;
	mIndices = indices;
	mVerticeSize = verticesize;
	mIndiceSize = indicesize;
	initMesh();
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
	glBufferData(GL_ARRAY_BUFFER, mVerticeSize, mVertices, GL_STATIC_DRAW);
	if (mIndices)
	{
		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndiceSize, mIndices, GL_STATIC_DRAW);
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void		Mesh::Bind()
{
	glBindVertexArray(mVAO);
}

void		Mesh::Draw()
{
	glBindVertexArray(mVAO);
	if (mIndices)
		glDrawElements(GL_TRIANGLES, mIndiceSize, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mVerticeSize / 3);
	glBindVertexArray(0);
}

}
