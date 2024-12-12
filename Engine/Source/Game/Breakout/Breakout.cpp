#include "Breakout.h"
#include "../../Managers/Managers.h"

#include "../../RHI/Shader.h"
#include "../../RHI/Character.h"

#include "../../Renderer/SpriteRenderer.h"
#include "../../Renderer/ImguiRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "../../Renderer/ParticleRenderer.h"

#include "../../Math/Math.h"

#include "../../Entities/GameObject.h"
#include "../../Entities/RenderableObject.h"
#include "../../Entities/Camera2D.h"

#include "../../Config/GlobalConfiguration.h"

#include <iostream>
#include <tuple>
#include <memory>

#include "Ball.h"
#include "GameLevel.h"
#include "../../Network/NetworkClient.h"
#include "../../Scene/Scene.h"
#include "../../Gui/Label.h"

#include "Paddle.h"
#include "ParticleGenerator.h"
#include "GameConfig.h"

int Breakout::Initialize()
{
	// Managers Initializing
	GameInstance::Initialize();
	g_pResourceManager->LoadTexture("Assets/Textures/background3.jpg", "background");
	g_pResourceManager->LoadTexture("Assets/Textures/particle.png", "particle");
	g_pResourceManager->LoadTexture("Assets/Textures/paddle.png", "paddle");
	g_pResourceManager->LoadTexture("Assets/Textures/block.png", "block");
	g_pResourceManager->LoadTexture("Assets/Textures/block_solid.png", "block_solid");
	g_pResourceManager->LoadTexture("Assets/Textures/awesomeface_transparent.png", "face_transparent");

	g_pResourceManager->LoadShader("Assets/Shaders/texture.vertex", "Assets/Shaders/texture.fragment", "texture_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/sprite.vertex", "Assets/Shaders/sprite.fragment", "sprite_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/text.vertex", "Assets/Shaders/text.fragment", "text_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/particle.vertex", "Assets/Shaders/particle.fragment", "particle_shader");

	g_pFontManager->LoadFont("Assets/Fonts/simsun.ttc");


	auto gConfig = Configuration::Get();
	camera = new Camera2D(gConfig->GetWidth(), gConfig->GetHeight());

	// Set Shader Uniform
	g_pResourceManager->GetShader("sprite_shader").Use()->SetInt("texture1", 0);
	g_pResourceManager->GetShader("sprite_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("text_shader").Use()->SetInt("text", 0);
	g_pResourceManager->GetShader("text_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("particle_shader").Use()->SetInt("sprite", 0);
	g_pResourceManager->GetShader("particle_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("texture_shader").Use()->SetInt("texture1", 0);

	std::shared_ptr<Scene> SceneLevel0 = std::make_shared<Scene>("SceneLevel0");
	std::shared_ptr<Scene> SceneLevel1 = std::make_shared<Scene>("SceneLevel1");
	std::shared_ptr<Scene> SceneLevel2 = std::make_shared<Scene>("SceneLevel2");
	std::shared_ptr<Scene> SceneLevel3 = std::make_shared<Scene>("SceneLevel3");

	std::shared_ptr <GameLevel> level0 = std::make_shared<GameLevel>();
	level0->Load("Assets/Level/level0.lvl", gConfig->GetWidth(), gConfig->GetHeight()/2);

	std::shared_ptr<Label> fpsLabel = std::make_shared<Label>(L"FPS:", 0.0f, 50.0f, 1.0f);

	std::shared_ptr<RenderableObject> backgroundObj = std::make_shared<RenderableObject>("background", 0, 0, gConfig->GetWidth(), gConfig->GetHeight(), Eigen::Vector3f{1.0f, 1.0f, 1.0f});

	Eigen::Vector2f playSize = { 100.0f, 20.0f };
	Eigen::Vector2f playerPos = Eigen::Vector2f(static_cast<float>(gConfig->GetWidth()) / 2.0f - playSize.x() / 2.0f, static_cast<float>(gConfig->GetHeight()) - playSize.y());
	std::shared_ptr<Paddle> Player = std::make_shared<Paddle>("paddle", playerPos.x(), playerPos.y(), playSize.x(), playSize.y(), Eigen::Vector3f{1.0f, 1.0f, 1.0f});

	Eigen::Vector2f ballPos = playerPos + Eigen::Vector2f(playSize.x() / 2.0f - BALL_RADIUS,
		-BALL_RADIUS * 2.0f);
	std::shared_ptr<Ball> BallObj = std::make_shared<Ball>("face_transparent", ballPos.x(), ballPos.y(), BALL_RADIUS*2, BALL_RADIUS * 2);

	std::shared_ptr<ParticleGenerator> Particles = std::make_shared<ParticleGenerator>("particle", 500, BallObj, 2, Eigen::Vector2f{ BallObj->GetRadius() / 2 , BallObj->GetRadius() / 2 });

	SceneLevel0->AddGameObject("level0", level0);
	SceneLevel0->AddGameObject("fpsLabel", fpsLabel);
	SceneLevel0->AddGameObject("background", backgroundObj);
	SceneLevel0->AddGameObject("paddle", Player);
	SceneLevel0->AddGameObject("ball", BallObj);
	SceneLevel0->AddGameObject("particles", Particles);

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
		if (g_pInputManager->IsKeyPressed("Left"))
		{
			for (auto obj : mCurrentScene->GetSceneObjects())
			{
				obj.second->OnKeyPressed("Left");
			}
		}
		if (g_pInputManager->IsKeyPressed("Right"))
		{
			for (auto obj : mCurrentScene->GetSceneObjects())
			{
				obj.second->OnKeyPressed("Right");
			}
		}
		if (g_pInputManager->IsKeyPressed("Space"))
		{
			for (auto obj : mCurrentScene->GetSceneObjects())
			{
				obj.second->OnKeyPressed("Space");
			}
		}
		if (g_pInputManager->IsKeyPressed("Enter"))
		{
			auto PaddleObj = dynamic_pointer_cast<Paddle>(mCurrentScene->GetGameObject("paddle"));
			auto BallObj = dynamic_pointer_cast<Ball>(mCurrentScene->GetGameObject("ball"));

			if (PaddleObj && BallObj)
			{
				auto gConfig = Configuration::Get();
				Eigen::Vector2f playSize = { 100.0f, 20.0f };
				Eigen::Vector2f playerPos = Eigen::Vector2f(gConfig->GetWidth() / 2.0f - playSize.x() / 2.0f, gConfig->GetHeight() - playSize.y());
				PaddleObj->SetSize(playSize);
				PaddleObj->SetPosition(playerPos[0], playerPos[1], 0.0f);
				BallObj->Reset({ PaddleObj->GetPosX()+PaddleObj->GetSizeX()/2 - BALL_RADIUS, PaddleObj->GetPosY()-(BALL_RADIUS*2)}, { 100.0f, -350.0f });
			}
		}
	}
}

void Breakout::Render()
{
	g_pGraphicsManager->GetSpriteRenderer()->Clear();
	g_pGraphicsManager->GetParticleRenderer()->Clear();
	g_pGraphicsManager->GetTextRenderer()->Clear();
	g_pGraphicsManager->GetImguiRenderer()->Clear();
	for (const auto& obj : mCurrentScene->GetSceneObjects())
	{
		if (obj.second)
		{
			obj.second->OnRender();
		}
	}
	g_pGraphicsManager->GetSpriteRenderer()->OnRender();
	g_pGraphicsManager->GetParticleRenderer()->OnRender();
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

		if (const auto fpsLabel = dynamic_pointer_cast<Label>(mCurrentScene->GetGameObject("fpsLabel")))
		{
			fpsLabel->SetText(L"FPS:" + std::to_wstring(g_pStatisticsManager->GetFPS()));
		}
	}
}

void Breakout::DetectCollide()
{
	 auto Level = dynamic_pointer_cast<GameLevel>(mCurrentScene->GetGameObject("level0"));
	if (Level)
	{
		auto BallObj = dynamic_pointer_cast<Ball>(mCurrentScene->GetGameObject("ball"));
		auto PaddleObj = dynamic_pointer_cast<Paddle>(mCurrentScene->GetGameObject("paddle"));
		const auto& Bricks = Level->GetBricks();

		for (const auto& brick : Bricks)
		{
			if (brick->IsDestroyed())
			{
				continue;
			}
			if (BallObj)
			{
				Collision collision = BallObj->CheckCollision(brick);
				if (std::get<0>(collision)) // if collision is true
				{
					// destroy block if not solid
					if (!brick->IsSolid())
					{
						brick->SetDestroyed(true);
					}
					BallObj->OnCollision(collision, brick);
				}
			}
		}
		if (PaddleObj)
		{
			Collision collision = BallObj->CheckCollision(std::shared_ptr<RenderableObject>(PaddleObj));
			BallObj->OnCollision(collision, PaddleObj);
		}
	}
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