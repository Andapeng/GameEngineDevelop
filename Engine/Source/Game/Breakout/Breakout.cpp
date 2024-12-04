#include "Breakout.h"
#include "../../Managers/Managers.h"

#include "../../RHI/Shader.h"
#include "../../RHI/Character.h"

#include "../../Renderer/SpriteRenderer.h"
#include "../../Renderer/ImguiRenderer.h"
#include "../../Renderer/TextRenderer.h"

#include "../../Math/Math.h"

#include "../../Entities/GameObject.h"
#include "../../Entities/RenderableObject.h"
#include "../../Entities/Camera2D.h"

#include "../../Config/GlobalConfiguration.h"

#include <iostream>

#include "GameLevel.h"
#include "../../Network/NetworkClient.h"
#include "../../Scene/Scene.h"
#include "../../Gui/Label.h"

#include "Paddle.h"

int Breakout::Initialize()
{
	// Managers Initializing
	GameInstance::Initialize();
	g_pResourceManager->LoadTexture("Assets/Textures/background3.jpg", "background");
	g_pResourceManager->LoadTexture("Assets/Textures/particle.png", "particle");
	g_pResourceManager->LoadTexture("Assets/Textures/paddle.png", "paddle");
	g_pResourceManager->LoadTexture("Assets/Textures/block.png", "block");
	g_pResourceManager->LoadTexture("Assets/Textures/block_solid.png", "block_solid");
	g_pResourceManager->LoadShader("Assets/Shaders/texture.vertex", "Assets/Shaders/texture.fragment", "texture_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/sprite.vertex", "Assets/Shaders/sprite.fragment", "sprite_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/text.vertex", "Assets/Shaders/text.fragment", "text_shader");
	g_pFontManager->LoadFont("Assets/Fonts/simsun.ttc");

	auto gConfig = Configuration::Get();
	camera = new Camera2D(gConfig->GetWidth(), gConfig->GetHeight());

	// Set Shader Uniform
	g_pResourceManager->GetShader("sprite_shader").Use()->SetInt("texture1", 0);
	g_pResourceManager->GetShader("sprite_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("text_shader").Use()->SetInt("text", 0);
	g_pResourceManager->GetShader("text_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("texture_shader").Use()->SetInt("texture1", 0);

	std::shared_ptr<Scene> SceneLevel0 = std::make_shared<Scene>("SceneLevel0");
	std::shared_ptr<Scene> SceneLevel1 = std::make_shared<Scene>("SceneLevel1");
	std::shared_ptr<Scene> SceneLevel2 = std::make_shared<Scene>("SceneLevel2");
	std::shared_ptr<Scene> SceneLevel3 = std::make_shared<Scene>("SceneLevel3");

	GameLevel* level0 = new GameLevel;
	level0->Load("Assets/Level/level0.lvl", gConfig->GetWidth(), gConfig->GetHeight()/2);

	Label* fpsLabel = new Label(L"FPS:", 0.0f, 50.0f, 1.0f);

	RenderableObject* backgroudObj = new RenderableObject("background", 0, 0, gConfig->GetWidth(), gConfig->GetHeight(), {1.0f, 1.0f, 1.0f});

	Eigen::Vector2f playSize = { 100.0f, 20.0f };
	Eigen::Vector2f playerPos = Eigen::Vector2f(gConfig->GetWidth() / 2.0f - 100.0f / 2.0f, gConfig->GetHeight() - 20.0f);
	Paddle* Player = new Paddle("paddle", playerPos.x(), playerPos.y(), playSize.x(), playSize.y(), {1.0f, 1.0f, 1.0f});

	SceneLevel0->AddGameObject("level0", level0);
	SceneLevel0->AddGameObject("fpsLabel", fpsLabel);
	SceneLevel0->AddGameObject("background", backgroudObj);
	SceneLevel0->AddGameObject("paddle", Player);

	g_pSceneManager->AddScene("SceneLevel0", SceneLevel0);
	g_pSceneManager->AddScene("SceneLevel1", SceneLevel1);
	g_pSceneManager->AddScene("SceneLevel2", SceneLevel2);
	g_pSceneManager->AddScene("SceneLevel3", SceneLevel3);

	Start();
	return 0;
}

int Breakout::Tick()
{
	return 0;
}

int Breakout::Release()
{
	return 0;
}

void Breakout::ProcessInput()
{
	if (IsRunning())
	{
		for (auto obj : mCurrentScene->GetSceneObjects())
		{
			if (obj.second)
			{
				obj.second->OnKeyPressed();
			}
		}
	}
}

void Breakout::Render()
{
	g_pGraphicsManager->GetSpriteRenderer()->Clear();
	g_pGraphicsManager->GetTextRenderer()->Clear();
	g_pGraphicsManager->GetImguiRenderer()->Clear();
	for (const auto& obj : mCurrentScene->GetSceneObjects())
	{
		obj.second->OnRender();
	}
	g_pGraphicsManager->GetSpriteRenderer()->OnRender();
	g_pGraphicsManager->GetTextRenderer()->OnRender();
	g_pGraphicsManager->GetImguiRenderer()->OnRender();

	if (!g_pStateManager->IsGameOver())
	{
		g_pGraphicsManager->Tick();
	}
}

void Breakout::Update(float elapsedTime)
{
	if (IsRunning()) {
		for (const auto& obj : mCurrentScene->GetSceneObjects())
		{
			if (obj.second)
			{
				obj.second->Update(elapsedTime);
			}
		}

		if (const auto fpsLabel = dynamic_cast<Label*>(mCurrentScene->GetGameObject("fpsLabel")))
		{
			fpsLabel->SetText(L"FPS:" + std::to_wstring(g_pStatisticsManager->GetFPS()));
		}
	}
}

void Breakout::DetectCollide()
{
}

bool Breakout::IsRunning()
{
	return g_pStateManager->IsGameRunning();
}

int Breakout::Stop()
{
	g_pStateManager->GameOver();
	return 0;
}

int Breakout::Pause()
{
	g_pStateManager->GamePause();
	return 0;
}

int Breakout::Start()
{
	if (g_pStateManager->IsGameOver())
	{
		mCurrentScene = g_pSceneManager->LoadScene("SceneLevel0");
	}

	g_pStateManager->GameStart();
	return 0;
}