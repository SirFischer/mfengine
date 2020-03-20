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
		mf::Camera								*mCamera = NULL;
		std::vector<Mesh *>						mMeshes;
		std::vector<StaticInstancingBatch *>	mInstancedBatch;
		std::vector<Light *>					mLights;

		GLenum									mDrawMode = GL_TRIANGLES;

		void						LoadLights(Shader *tShader);

	public:
		Renderer(mf::Camera *tCamera);
		~Renderer();

		void						SetDrawMode(GLenum tMode){mDrawMode = tMode;}

		void						AddMesh(Mesh *tMesh);
		void						AddModel(Model *tModel);
		void						AddInstanceBatch(StaticInstancingBatch *tBatch);
		void						AddLights(Light *tLights);
		void						Render();
	};
}
