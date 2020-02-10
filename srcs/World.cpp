#include "World.hpp"

World::World(mf::ResourceManager *tResourceManager, mf::Camera	*tCamera, mf::Player *tPlayer)
:mResourceManager(tResourceManager)
,mLevelTerrain(1000, 1000)
,mSkybox(tResourceManager->LoadImage("assets/textures/skybox/CloudyCrown_Sunset_Front.png"),
		 tResourceManager->LoadImage("assets/textures/skybox/CloudyCrown_Sunset_Left.png"),
		 tResourceManager->LoadImage("assets/textures/skybox/CloudyCrown_Sunset_Back.png"),
		 tResourceManager->LoadImage("assets/textures/skybox/CloudyCrown_Sunset_Right.png"),
		 tResourceManager->LoadImage("assets/textures/skybox/CloudyCrown_Sunset_Up.png"),
		 tResourceManager->LoadImage("assets/textures/skybox/CloudyCrown_Sunset_Down.png"))
{
	mCamera = tCamera;
	mPlayer = tPlayer;
	mResourceManager->LoadShader("terrain", "assets/shaders/vertex/terrain.glsl", "assets/shaders/fragment/terrain.glsl");
	mLevelTerrain.SetShaderProgram(mResourceManager->GetShader("terrain"));
	mLevelTerrain.SetProjectionMatrix(tCamera->GetProjectionMatrix());
	mLevelTerrain.SetTexture(mResourceManager->LoadImage("assets/textures/terrain/grass_grass_0131_01.jpg"));
	glm::mat4 scale = glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 0)), glm::vec3(5, 90.0, 5));
	mLevelTerrain.SetTransformMatrix(scale);
	mLevelTerrain.GenHeightMap(time(0), 0, 5, 0, 5);

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
	
	mTestModel.LoadFromOBJ("assets/objects/Tree.obj");
	mTestModel.SetProjectionMatrix(mCamera->GetProjectionMatrix());
	mTestModel.SetShaderProgram(mResourceManager->GetShader("terrain"));
	scale = glm::scale(glm::translate(glm::mat4(1.0), glm::vec3(0, mLevelTerrain.GetHeightInWorld(0, 0) - 0.5, 0)), glm::vec3(10, 10.0, 10));
	mTestModel.SetTransformMatrix(scale);
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
	mPlayer->HandleTerrainCollision(&mLevelTerrain);
	mTestModel.SetViewMatrix(mCamera->GetViewMatrix());
}

void	World::Draw(mf::Renderer *tRenderer)
{
	tRenderer->AddMesh(&mLevelTerrain);
	mSkybox.Draw(tRenderer);
	tRenderer->AddLights(&mLight);
	tRenderer->AddLights(&mLight2);
	mTestModel.Draw(GL_TRIANGLES);
	tRenderer->Render();
}