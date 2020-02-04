#pragma once

#include "Mesh.hpp"
#include "Light.hpp"
#include "Skybox.hpp"
#include "Terrain.hpp"

namespace mf
{
	class Renderer
	{
	private:
		std::vector<Mesh *>			mMeshes;
		std::vector<Light *>		mLights;

		void						LoadLights();

	public:
		Renderer(/* args */);
		~Renderer();

		void						AddMesh(Mesh *tMesh);
		void						AddLights(Light *tLights);
		void						Render();
	};
}
