#include "World.hpp"

World::World(mf::ResourceManager *tResourceManager, glm::mat4 tProjectionMatrix)
:mResourceManager(tResourceManager)
,mLevelTerrain(400, 400)
,mSkybox(tResourceManager->LoadImage("assets/textures/skybox/skybox_texture.jpg"))
{
	mLevelTerrain.GenHeightMap(time(0), 0, 5, 0, 5);
	mResourceManager->LoadShader("terrain", "assets/shaders/vertex/terrain.glsl", "assets/shaders/fragment/terrain.glsl");
	mLevelTerrain.SetShaderProgram(mResourceManager->GetShader("terrain"));
	mLevelTerrain.SetProjectionMatrix(tProjectionMatrix);
	mLevelTerrain.SetTexture(mResourceManager->LoadImage("assets/textures/terrain/grass_grass_0131_01.jpg"));
	glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(2, 50.0, 2));
	mLevelTerrain.SetTransformMatrix(scale);

	mResourceManager->LoadShader("skybox", "assets/shaders/vertex/skybox.glsl", "assets/shaders/fragment/skybox.glsl");
	mSkybox.SetShaderProgram(mResourceManager->GetShader("skybox"));
	mSkybox.SetProjectionMatrix(tProjectionMatrix);
	mSkybox.SetTransformMatrix(glm::scale(glm::mat4(1.0), glm::vec3(300, 300, 300)));
}

World::~World()
{
}

void	World::Update(glm::mat4 tViewMatrix)
{
	mLevelTerrain.SetViewMatrix(tViewMatrix);
	mSkybox.SetViewMatrix(tViewMatrix);
}

void	World::Draw()
{
	mLevelTerrain.Draw(GL_TRIANGLES);
	mSkybox.Draw(GL_TRIANGLES);
}