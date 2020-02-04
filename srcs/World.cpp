#include "World.hpp"

World::World(mf::ResourceManager *tResourceManager, mf::Camera	*tCamera)
:mResourceManager(tResourceManager)
,mLevelTerrain(400, 400)
,mSkybox(tResourceManager->LoadImage("assets/textures/skybox/skybox_texture.jpg"))
{
	mLevelTerrain.GenHeightMap(time(0), 0, 4.5, 0, 4.5);
	mResourceManager->LoadShader("terrain", "assets/shaders/vertex/terrain.glsl", "assets/shaders/fragment/terrain.glsl");
	mLevelTerrain.SetShaderProgram(mResourceManager->GetShader("terrain"));
	mLevelTerrain.SetProjectionMatrix(tCamera->GetProjectionMatrix());
	mLevelTerrain.SetTexture(mResourceManager->LoadImage("assets/textures/terrain/grass_grass_0131_01.jpg"));
	glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(1, 30.0, 1));
	mLevelTerrain.SetTransformMatrix(scale);

	mResourceManager->LoadShader("skybox", "assets/shaders/vertex/skybox.glsl", "assets/shaders/fragment/skybox.glsl");
	mSkybox.SetShaderProgram(mResourceManager->GetShader("skybox"));
	mSkybox.SetProjectionMatrix(tCamera->GetProjectionMatrix());
	mSkybox.SetTransformMatrix(glm::scale(glm::mat4(1.0), glm::vec3(300, 300, 300)));

	mLight.SetAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
	mLight.SetPosition(glm::vec3(50.f, 10.f, 50.f));
	mLight.SetDiffuseLight(glm::vec3(50.1f, 0.1f, 0.1f));
	mLight.SetSpecularLight(glm::vec3(0.5, 0.5, 0.5));

	mLight2.SetAmbientLight(glm::vec3(0.0f, 0.0f, 0.0f));
	mLight2.SetPosition(glm::vec3(-50.f, 10.f, -50.f));
	mLight2.SetDiffuseLight(glm::vec3(0.1f, 50.1f, 0.1f));
	mLight2.SetSpecularLight(glm::vec3(0.5, 0.5, 0.5));

}

World::~World()
{
}

void	World::Update(glm::mat4 tViewMatrix)
{
	static float xpos = 0; 
	mLevelTerrain.SetViewMatrix(tViewMatrix);
	mLight.SetPosition(glm::vec3(cos(xpos) * 150, (60.f), sin(xpos) * 150));
	mLight2.SetPosition(glm::vec3(sin(xpos) * 150, (60.f), cos(xpos) * 150));
	mSkybox.SetViewMatrix(tViewMatrix);
	xpos += 0.05;
}

void	World::Draw(mf::Renderer *tRenderer)
{
	tRenderer->AddMesh(&mLevelTerrain);
	tRenderer->AddMesh(&mSkybox);
	tRenderer->AddLights(&mLight);
	tRenderer->AddLights(&mLight2);
	tRenderer->Render();
}