#pragma once
#include "Terrain.hpp"

class World
{
private:
	mf::ResourceManager		*mResourceManager;

	mf::Terrain				mLevelTerrain;

public:
			World(mf::ResourceManager *tResourceManager, glm::mat4 tProjectionMatrix);
			~World();

	void	Update(glm::mat4 tViewMatrix);
	void	Draw();
};
