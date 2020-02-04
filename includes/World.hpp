#pragma once
#include "Renderer.hpp"

#include "Camera.hpp"

#include "Terrain.hpp"
#include "Skybox.hpp"

class World
{
private:
	mf::ResourceManager		*mResourceManager;
	mf::Camera				*mCamera;

	mf::Terrain				mLevelTerrain;
	mf::Skybox				mSkybox;

	mf::Light				mLight;

public:
			World(mf::ResourceManager *tResourceManager, mf::Camera	*tCamera);
			~World();

	void	Update(glm::mat4 tViewMatrix);
	void	Draw(mf::Renderer *tRenderer);
};
