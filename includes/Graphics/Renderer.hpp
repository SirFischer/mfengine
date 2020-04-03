#pragma once
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Terrain.hpp"
#include "Model.hpp"
#include "StaticInstancingBatch.hpp"

namespace mf
{
	class Renderer
	{
	private:
		Renderer();
		~Renderer();

		static std::vector<Mesh *>						mMeshes;
		static std::vector<StaticInstancingBatch *>		mInstancedBatch;
		static std::vector<Light *>						mLights;

		static void										LoadLights(Shader *tShader);

	public:
		static mf::Camera				*mCamera;
		static GLenum					mDrawMode;

		static void						AddMesh(Mesh *tMesh);
		static void						AddModel(Model *tModel);
		static void						AddInstanceBatch(StaticInstancingBatch *tBatch);
		static void						AddLights(Light *tLights);
		static void						Render();
	};
}
