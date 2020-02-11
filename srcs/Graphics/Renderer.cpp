#include "Renderer.hpp"

namespace mf
{
	Renderer::Renderer(mf::Camera *tCamera)
	{
		mCamera = tCamera;
	}

	Renderer::~Renderer()
	{
	}

	void		Renderer::AddMesh(Mesh *tMesh)
	{
		mMeshes.push_back(tMesh);
	}

	void						Renderer::AddModel(Model *tModel)
	{
		std::vector<Mesh *>		mMeshes = tModel->GetMeshes();
		for (auto &i : mMeshes)
		{
			this->AddMesh(i);
		}
	}

	void		Renderer::AddLights(Light *tLights)
	{
		mLights.push_back(tLights);
	}

	void		Renderer::LoadLights()
	{
		int i = 0;
		while (i < (int)mLights.size())
		{
			mMeshes.back()->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].ambient", mLights[i]->GetAmbientLight());
			mMeshes.back()->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].position", mLights[i]->GetPosition());
			mMeshes.back()->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].diffuse", mLights[i]->GetDiffuseLight());
			mMeshes.back()->GetShaderProgram()->SetVec3("lights[" + std::to_string(i) + "].specular", mLights[i]->GetSpecularLight());
			mMeshes.back()->GetShaderProgram()->SetInt("lights[" + std::to_string(i) + "].specular_pow", mLights[i]->GetSpecularPower());
			mMeshes.back()->GetShaderProgram()->SetFloat("lights[" + std::to_string(i) + "].specular_strength", mLights[i]->GetSpecularStrength());
			i++;
		}
		mMeshes.back()->GetShaderProgram()->SetInt("lightNum", i);
		mMeshes.back()->GetShaderProgram()->SetVec3("viewPos", mCamera->GetPos());
	}

	void		Renderer::Render()
	{
		while (mMeshes.size())
		{
			mMeshes.back()->PrepareShader();
			LoadLights();
			mMeshes.back()->Draw(GL_TRIANGLES);
			mMeshes.pop_back();
		}
		mLights.clear();
	}
} // namespace mf
