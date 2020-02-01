#pragma once
#include "Terrain.hpp"
#include "Skybox.hpp"

class World
{
private:
	mf::ResourceManager		*mResourceManager;

	mf::Terrain				mLevelTerrain;
	mf::Skybox				mSkybox;

public:
			World(mf::ResourceManager *tResourceManager, glm::mat4 tProjectionMatrix);
			~World();

	void	Update(glm::mat4 tViewMatrix);
	void	Draw();
};
