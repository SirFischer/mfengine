#include "World.hpp"

World::World(mf::ResourceManager *tResourceManager, mf::Camera	*tCamera, mf::Player *tPlayer)
:mResourceManager(tResourceManager)
,mLevelTerrain(300, 300)
,mSkybox(tResourceManager->LoadImage("assets/textures/skybox/Embassyft.tga"),
		 tResourceManager->LoadImage("assets/textures/skybox/Embassylf.tga"),
		 tResourceManager->LoadImage("assets/textures/skybox/Embassybk.tga"),
		 tResourceManager->LoadImage("assets/textures/skybox/Embassyrt.tga"),
		 tResourceManager->LoadImage("assets/textures/skybox/Embassyup.tga"),
		 tResourceManager->LoadImage("assets/textures/skybox/Embassydn.tga"))
{
	mCamera = tCamera;
	mPlayer = tPlayer;
	mResourceManager->LoadShader("terrain", "assets/shaders/vertex/terrain.glsl", "assets/shaders/fragment/terrain.glsl");
	mLevelTerrain.SetShaderProgram(mResourceManager->GetShader("terrain"));
	mLevelTerrain.SetProjectionMatrix(tCamera->GetProjectionMatrix());
	mLevelTerrain.SetTexture(mResourceManager->LoadImage("assets/textures/terrain/grass_grass_0131_01.jpg"));
	glm::mat4 scale = glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0)), glm::vec3(1, 50.0, 1));
	mLevelTerrain.SetTransformMatrix(scale);
	mLevelTerrain.GenHeightMap(0, 0, 1, 0, 1);

	mResourceManager->LoadShader("skybox", "assets/shaders/vertex/skybox.glsl", "assets/shaders/fragment/skybox.glsl");
	mSkybox.SetShaderProgram(mResourceManager->GetShader("skybox"));
	mSkybox.SetProjectionMatrix(tCamera->GetProjectionMatrix());
	mSkybox.SetTransformMatrix(glm::scale(glm::mat4(1.0), glm::vec3(450, 450, 450)));

	mLight.SetAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
	mLight.SetPosition(glm::vec3(50.f, 10.f, 50.f));
	mLight.SetDiffuseLight(glm::vec3(50.1f, 0.1f, 0.1f));
	mLight.SetSpecularLight(glm::vec3(0.45, 0.55, 0.45));

	mLight2.SetAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
	mLight2.SetPosition(glm::vec3(50.f, 60.f, 50.f));
	mLight2.SetDiffuseLight(glm::vec3(0.1f, 30.1f, 0.1f));
	mLight2.SetSpecularLight(glm::vec3(0.85, 0.95, 0.85));
}

World::~World()
{
}

void	World::Update(glm::mat4 tViewMatrix)
{
	static float xpos = 0;

	mLevelTerrain.SetViewMatrix(tViewMatrix);
	mLight.SetPosition(glm::vec3(cos(xpos) * 150, (70.f), sin(xpos) * 150));
	mSkybox.SetViewMatrix(glm::mat4(glm::mat3(tViewMatrix)));
	xpos += 0.05;
	float terrainHeight = mLevelTerrain.GetHeightInWorld(mPlayer->GetPosition().x, mPlayer->GetPosition().z);
	if (mPlayer->GetPosition().y - 2 < terrainHeight)
	{
		glm::vec3 pos = mPlayer->GetPosition();
		pos.y = terrainHeight + 2;
		mPlayer->SetPosition(pos);
	}
	else
	{
		mPlayer->MoveDown();
	}
}

void	World::Draw(mf::Renderer *tRenderer)
{
	tRenderer->AddMesh(&mLevelTerrain);
	mSkybox.Draw(tRenderer);
	tRenderer->AddLights(&mLight);
	tRenderer->AddLights(&mLight2);
	tRenderer->Render();
}