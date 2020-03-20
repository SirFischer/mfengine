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

	void		Renderer::AddModel(Model *tModel)
	{
		std::vector<Mesh *>		mMeshes = tModel->GetMeshes();
		for (auto &i : mMeshes)
		{
			this->AddMesh(i);
		}
	}

	void		Renderer::AddInstanceBatch(StaticInstancingBatch *tBatch)
	{
		mInstancedBatch.push_back(tBatch);
	}

	void		Renderer::AddLights(Light *tLights)
	{
		mLights.push_back(tLights);
	}

	void		Renderer::LoadLights(Shader *tShader)
	{
		int i = 0;
		while (i < (int)mLights.size())
		{
			tShader->SetVec3("lights[" + std::to_string(i) + "].ambient", mLights[i]->GetAmbientLight());
			tShader->SetVec3("lights[" + std::to_string(i) + "].position", mLights[i]->GetPosition());
			tShader->SetVec3("lights[" + std::to_string(i) + "].diffuse", mLights[i]->GetDiffuseLight());
			tShader->SetVec3("lights[" + std::to_string(i) + "].specular", mLights[i]->GetSpecularLight());
			tShader->SetInt("lights[" + std::to_string(i) + "].specular_pow", mLights[i]->GetSpecularPower());
			tShader->SetFloat("lights[" + std::to_string(i) + "].specular_strength", mLights[i]->GetSpecularStrength());
			i++;
		}
		tShader->SetInt("lightNum", i);
		tShader->SetVec3("viewPos", mCamera->GetPos());
	}

	void		Renderer::Render()
	{
		while (mMeshes.size())
		{
			mMeshes.back()->PrepareShader();
			LoadLights(mMeshes.back()->GetShaderProgram());
			mMeshes.back()->Draw(mDrawMode);
			mMeshes.pop_back();
		}
		while (mInstancedBatch.size())
		{
			mInstancedBatch.back()->Draw(mDrawMode, mLights, mCamera);
			mInstancedBatch.pop_back();
		}
		mLights.clear();
	}
} // namespace mf
