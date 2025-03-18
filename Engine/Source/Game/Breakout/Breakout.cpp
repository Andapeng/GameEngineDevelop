#include "Breakout.h"
#include "../../Managers/Managers.h"

#include "../../RHI/Shader.h"
#include "../../RHI/Character.h"

#include "../../Renderer/SpriteRenderer.h"
#include "../../Renderer/ImguiRenderer.h"
#include "../../Renderer/TextRenderer.h"
#include "../../Renderer/ParticleRenderer.h"

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
#include "PowerUp.h"
#include "PowerUpSpawner.h"
#include "../../Renderer/PostProcessingRenderer.h"

float ShakeTime = 0.0f;
Configuration* g_pConfig = nullptr;

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
	g_pResourceManager->LoadTexture("Assets/Textures/powerup_chaos.png", "powerup_chaos");
	g_pResourceManager->LoadTexture("Assets/Textures/powerup_confuse.png", "powerup_confuse");
	g_pResourceManager->LoadTexture("Assets/Textures/powerup_increase.png", "powerup_increase");
	g_pResourceManager->LoadTexture("Assets/Textures/powerup_passthrough.png", "powerup_passthrough");
	g_pResourceManager->LoadTexture("Assets/Textures/powerup_speed.png", "powerup_speed");
	g_pResourceManager->LoadTexture("Assets/Textures/powerup_sticky.png", "powerup_sticky");


	g_pResourceManager->LoadShader("Assets/Shaders/texture.vertex", "Assets/Shaders/texture.fragment", "texture_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/sprite.vertex", "Assets/Shaders/sprite.fragment", "sprite_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/text.vertex", "Assets/Shaders/text.fragment", "text_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/particle.vertex", "Assets/Shaders/particle.fragment", "particle_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/postprocessing.vertex", "Assets/Shaders/postprocessing.fragment", "postprocessing_shader");


	g_pFontManager->LoadFont("Assets/Fonts/simsun.ttc");


	g_pConfig = Configuration::Get();
	camera = new Camera2D(g_pConfig->GetWidth(), g_pConfig->GetHeight());

	// Set Shader Uniform
	g_pResourceManager->GetShader("sprite_shader").Use()->SetInt("texture1", 0);
	g_pResourceManager->GetShader("sprite_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("text_shader").Use()->SetInt("text", 0);
	g_pResourceManager->GetShader("text_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("particle_shader").Use()->SetInt("sprite", 0);
	g_pResourceManager->GetShader("particle_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("texture_shader").Use()->SetInt("texture1", 0);

	std::shared_ptr<Scene> SceneLevel = std::make_shared<Scene>("SceneLevel");

	std::shared_ptr <GameLevel> level0 = std::make_shared<GameLevel>();
	std::shared_ptr <GameLevel> level1 = std::make_shared<GameLevel>();
	std::shared_ptr <GameLevel> level2 = std::make_shared<GameLevel>();
	std::shared_ptr <GameLevel> level3 = std::make_shared<GameLevel>();

	level0->Load("Assets/Level/level0.lvl", g_pConfig->GetWidth(), g_pConfig->GetHeight() / 2);
	level1->Load("Assets/Level/level1.lvl", g_pConfig->GetWidth(), g_pConfig->GetHeight() / 2);
	level2->Load("Assets/Level/level2.lvl", g_pConfig->GetWidth(), g_pConfig->GetHeight() / 2);
	level3->Load("Assets/Level/level3.lvl", g_pConfig->GetWidth(), g_pConfig->GetHeight() / 2);

	mGameLevels.push_back(level0);
	mGameLevels.push_back(level1);
	mGameLevels.push_back(level2);
	mGameLevels.push_back(level3);

	std::shared_ptr<Label> fpsLabel = std::make_shared<Label>(L"FPS:", 0.0f, 50.0f, 1.0f);
	std::shared_ptr<Label> livesLabel = std::make_shared<Label>(std::format(L"lives:{}", mLives), 0.0f, 0.0f, 1.0f);
	std::shared_ptr<Label> StartHint = std::make_shared<Label>(L"Press ENTER to start", 180.0f, g_pConfig->GetHeight()/2.0f, 1.0f);
	std::shared_ptr<Label> SelectLevelHint = std::make_shared<Label>(L"Press W or S to select level", 170.0f, g_pConfig->GetHeight() / 2.0f + 40.0f, 0.75f);

	std::shared_ptr<Label> WinHint = std::make_shared<Label>(L"You WON!!!", 300.0f, g_pConfig->GetHeight() / 2.0f, 1.0f);
	std::shared_ptr<Label> RestartHint = std::make_shared<Label>(L"Press ENTER to retry or ESC to quit", 80.0f, g_pConfig->GetHeight() / 2.0f + 40.0f, 0.75f);
	WinHint->SetVisible(false);
	RestartHint->SetVisible(false);

	std::shared_ptr<RenderableObject> backgroundObj = std::make_shared<RenderableObject>("background", 0, 0, g_pConfig->GetWidth(), g_pConfig->GetHeight(), Eigen::Vector3f{1.0f, 1.0f, 1.0f});

	Eigen::Vector2f playSize = { 100.0f, 20.0f };
	Eigen::Vector2f playerPos = Eigen::Vector2f(static_cast<float>(g_pConfig->GetWidth()) / 2.0f - playSize.x() / 2.0f, static_cast<float>(g_pConfig->GetHeight()) - playSize.y());
	std::shared_ptr<Paddle> Player = std::make_shared<Paddle>("paddle", playerPos.x(), playerPos.y(), playSize.x(), playSize.y(), Eigen::Vector3f{1.0f, 1.0f, 1.0f});

	Eigen::Vector2f ballPos = playerPos + Eigen::Vector2f(playSize.x() / 2.0f - BALL_RADIUS,
		-BALL_RADIUS * 2.0f);
	std::shared_ptr<Ball> BallObj = std::make_shared<Ball>("face_transparent", ballPos.x(), ballPos.y(), BALL_RADIUS*2, BALL_RADIUS * 2);

	std::shared_ptr<ParticleGenerator> Particles = std::make_shared<ParticleGenerator>("particle", 500, BallObj, 2, Eigen::Vector2f{ BallObj->GetRadius() / 2 , BallObj->GetRadius() / 2 });

	std::shared_ptr<PowerUpSpawner> powerUpSpawner = std::make_shared<PowerUpSpawner>();

	SceneLevel->AddGameObject("level", mGameLevels[mLevel]);
	SceneLevel->AddGameObject("fpsLabel", fpsLabel);
	SceneLevel->AddGameObject("livesLabel", livesLabel);
	SceneLevel->AddGameObject("StartHint", StartHint);
	SceneLevel->AddGameObject("SelectLevelHint", SelectLevelHint);
	SceneLevel->AddGameObject("WinHint", WinHint);
	SceneLevel->AddGameObject("RestartHint", RestartHint);
	SceneLevel->AddGameObject("background", backgroundObj);
	SceneLevel->AddGameObject("paddle", Player);
	SceneLevel->AddGameObject("ball", BallObj);
	SceneLevel->AddGameObject("particles", Particles);
	SceneLevel->AddGameObject("powerUpSpawner", powerUpSpawner);

	g_pSceneManager->AddScene("SceneLevel", SceneLevel);
	mCurrentScene = g_pSceneManager->LoadScene(std::string("SceneLevel"));

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
		if (g_pInputManager->IsKeyPressed("W"))
		{
			previousLevel();
		}
		if (g_pInputManager->IsKeyPressed("S"))
		{
			nextLevel();
		}
	}

	if (g_pInputManager->IsKeyPressed("Enter"))
	{
		Start();
		showMenu(false);
		showGameOver(false);
	}
	if (g_pInputManager->IsKeyPressed("Esc"))
	{
		showGameOver(false);
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
	g_pGraphicsManager->GetPostProcessingRenderer()->BeginRender();
	g_pGraphicsManager->GetSpriteRenderer()->OnRender();
	g_pGraphicsManager->GetParticleRenderer()->OnRender();
	g_pGraphicsManager->GetPostProcessingRenderer()->EndRender();
	g_pGraphicsManager->GetPostProcessingRenderer()->OnRender();
	g_pGraphicsManager->GetTextRenderer()->OnRender();
	g_pGraphicsManager->GetImguiRenderer()->OnRender();

	if (!g_pStateManager->IsGameOver())
	{
		g_pGraphicsManager->Tick();
	}
}

void Breakout::Update(float elapsedTime)
{
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

	if (const auto livesLabel = dynamic_pointer_cast<Label>(mCurrentScene->GetGameObject("livesLabel")))
	{
		livesLabel->SetText(std::format(L"lives:{}", mLives));
	}

	if (ShakeTime > 0.0f)
	{
		ShakeTime -= elapsedTime;
		if (ShakeTime <= 0.0f)
		{
			g_pGraphicsManager->GetPostProcessingRenderer()->SetShake(false);
		}
	}

	// check loss condition
	auto BallObj = dynamic_pointer_cast<Ball>(mCurrentScene->GetGameObject("ball"));
	if (BallObj->GetPosY() >= g_pConfig->GetHeight()) // did ball reach bottom edge?
	{
		--this->mLives;
		// did the player lose all his lives? : game over
		if (this->mLives == 0)
		{
			this->resetLevel();
			Stop();
		}
		this->resetPlayer();
	}

	if (IsRunning()) {
		if (const auto CurrentLevel = dynamic_pointer_cast<GameLevel>(mGameLevels[mLevel]))
		{
			if(CurrentLevel->IsCompleted())
			{
				resetLevel();
				resetPlayer();
				showGameOver(true);
			}
		}
	}
}

void Breakout::DetectCollide()
{
	 auto Level = dynamic_pointer_cast<GameLevel>(mCurrentScene->GetGameObject("level"));
	 auto powerUpSpawner = dynamic_pointer_cast<PowerUpSpawner>(mCurrentScene->GetGameObject("powerUpSpawner"));
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
						powerUpSpawner->SpawnPowerUps(brick);
					}
					else
					{
						ShakeTime = 0.05f;
						g_pGraphicsManager->GetPostProcessingRenderer()->SetShake(true);
						
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
		for (auto& powerUp : powerUpSpawner->GetPowerUps())
		{
			if(!powerUp->IsDestroyed())
			{
				if (powerUp->GetPosY() > g_pConfig->GetHeight())
				{
					powerUp->SetDestroyed(true);
				}
				bool isPowerUpActivated = PaddleObj->CheckCollision(powerUp);
				if (isPowerUpActivated)
				{
					powerUpSpawner->ActivatePowerUp(powerUp);
					powerUp->SetDestroyed(true);
					powerUp->SetActivated(true);
				}
			}
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
		mCurrentScene = g_pSceneManager->LoadScene(std::string("SceneLevel"));
	}

	g_pStateManager->GameStart();
	return 0;
}

void Breakout::previousLevel()
{
	mLevel--;
	if (mLevel < 0)
	{
		mLevel = MAX_LEVEL;
	}
	g_pSceneManager->GetScene("SceneLevel")->AddGameObject("level", mGameLevels[mLevel]);
}

void Breakout::nextLevel()
{
	mLevel++;
	if (mLevel > MAX_LEVEL)
	{
		mLevel = 0;
	}
	g_pSceneManager->GetScene("SceneLevel")->AddGameObject("level", mGameLevels[mLevel]);
}

void Breakout::resetLevel()
{
	const auto CurrentLevel = dynamic_pointer_cast<GameLevel>(mGameLevels[mLevel]);
	if (CurrentLevel)
	{
		CurrentLevel->Reload();
		mLives = MAX_LIVES;
	}
}

void Breakout::resetPlayer()
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
		BallObj->Reset({ PaddleObj->GetPosX() + PaddleObj->GetSizeX() / 2 - BALL_RADIUS, PaddleObj->GetPosY() - (BALL_RADIUS * 2) }, { 100.0f, -350.0f });
	}
}

void Breakout::showMenu(bool bIsShow)
{
	auto StartHint = dynamic_pointer_cast<Label>(mCurrentScene->GetGameObject("StartHint"));
	auto SelectLevelHint = dynamic_pointer_cast<Label>(mCurrentScene->GetGameObject("SelectLevelHint"));
	if (StartHint && SelectLevelHint)
	{
		StartHint->SetVisible(bIsShow);
		SelectLevelHint->SetVisible(bIsShow);
	}
}

void Breakout::showGameOver(bool bIsShow)
{
	auto WinHint = dynamic_pointer_cast<Label>(mCurrentScene->GetGameObject("WinHint"));
	auto RestartHint = dynamic_pointer_cast<Label>(mCurrentScene->GetGameObject("RestartHint"));
	if (WinHint && RestartHint)
	{
		WinHint->SetVisible(bIsShow);
		RestartHint->SetVisible(bIsShow);
	}
}
