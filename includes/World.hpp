#pragma once
#include "Renderer.hpp"

#include "Player.hpp"
#include "Camera.hpp"
#include "Terrain.hpp"
#include "Skybox.hpp"
#include "Model.hpp"



class World
{
private:
	mf::ResourceManager		*mResourceManager;
	mf::Camera				*mCamera;
	mf::Player				*mPlayer;

	mf::Terrain				mLevelTerrain;
	mf::Skybox				mSkybox;

	mf::Light				mLight;
	mf::Light				mLight2;

	mf::Model				mTreeModel;
	std::unique_ptr<mf::StaticInstancingBatch> mTrees;
	mf::Model				mGrassModel;
	std::unique_ptr<mf::StaticInstancingBatch> mGrass;

	mf::Model				mTestModel;

public:
			World(mf::ResourceManager *tResourceManager, mf::Camera	*tCamera, mf::Player *tPlayer);
			~World();

	void	Update(glm::mat4 tViewMatrix);
	void	Draw(mf::Renderer *tRenderer);
};
