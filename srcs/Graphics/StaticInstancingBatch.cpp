#include "StaticInstancingBatch.hpp"

namespace mf
{
StaticInstancingBatch::StaticInstancingBatch(Model	*tModel)
{
	mMeshes = tModel->GetMeshes();
}

StaticInstancingBatch::StaticInstancingBatch(Mesh	*tMesh)
{
	mMeshes.push_back(tMesh);
}

StaticInstancingBatch::~StaticInstancingBatch()
{
}

void			StaticInstancingBatch::AddInstance(glm::mat4 tTransform)
{
	if (mFinalized)
		return ;
	mTransformMatrices.push_back(tTransform);
}

void			StaticInstancingBatch::Finalize()
{
	if (mFinalized)
		return ;
	mFinalized = true;
	glGenBuffers(1, &mTransformBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mTransformBuffer);
	glBufferData(GL_ARRAY_BUFFER, mTransformMatrices.size() * sizeof(glm::mat4), &mTransformMatrices.data()[0], GL_STATIC_DRAW);
	for (auto &mesh : mMeshes)
	{
		mesh->Bind();

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
		
		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
}

void			StaticInstancingBatch::Draw(GLenum mode, std::vector<Light *> tLights, Camera *tCamera)
{
	if (!mFinalized)
		this->Finalize();
	for (auto &mesh : mMeshes)
	{
		mesh->PrepareShader();
		int i = 0;
		while (i < (int)tLights.size())
		{
			mesh->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].ambient", tLights[i]->GetAmbientLight());
			mesh->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].position", tLights[i]->GetPosition());
			mesh->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].diffuse", tLights[i]->GetDiffuseLight());
			mesh->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].specular", tLights[i]->GetSpecularLight());
			mesh->GetShaderProgram()->SetInt("lights[" + std::to_string(i) + "].specular_pow", tLights[i]->GetSpecularPower());
			mesh->GetShaderProgram()->SetFloat("lights[" + std::to_string(i) + "].specular_strength", tLights[i]->GetSpecularStrength());
			i++;
		}
		mesh->GetShaderProgram()->SetInt("lightNum", i);
		mesh->GetShaderProgram()->SetVec3("viewPos", tCamera->GetPos());
		glDrawArraysInstanced(mode, 0, mesh->GetVerticesSize() / 3, mTransformMatrices.size());
		glBindVertexArray(0);
	}
}

} // namespace mf
