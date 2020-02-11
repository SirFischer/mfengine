#pragma once
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Terrain.hpp"
#include "Model.hpp"

namespace mf
{
	class Renderer
	{
	private:
		mf::Camera					*mCamera = NULL;
		std::vector<Mesh *>			mMeshes;
		std::vector<Light *>		mLights;

		void						LoadLights();

	public:
		Renderer(mf::Camera *tCamera);
		~Renderer();

		void						AddMesh(Mesh *tMesh);
		void						AddModel(Model *tModel);
		void						AddLights(Light *tLights);
		void						Render();
	};
}
