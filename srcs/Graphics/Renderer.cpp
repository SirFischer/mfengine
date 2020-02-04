#include "Renderer.hpp"

namespace mf
{
	Renderer::Renderer(/* args */)
	{
	}

	Renderer::~Renderer()
	{
	}

	void		Renderer::AddMesh(Mesh *tMesh)
	{
		mMeshes.push_back(tMesh);
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
			i++;
		}
		mMeshes.back()->GetShaderProgram()->SetInt("lightNum", i);
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
