#pragma once

#include "Mesh.hpp"

namespace mf
{
	class Skybox : public Mesh
	{
	private:
		void	InitSkybox();
	public:
		Skybox(sf::Image tSkybox);
		~Skybox();
	};
	
} // namespace mf
