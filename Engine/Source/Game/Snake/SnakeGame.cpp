#include "SnakeGame.h"

#include "../../Managers/Managers.h"

#include "../../RHI/Shader.h"
#include "../../RHI/Texture.h"
#include "../../RHI/Character.h"

#include "../../Math/Math.h"

#include "../../Entities/GameObject.h"
#include "../../Entities/RenderableObject.h"
#include "../../Entities/Player.h"
#include "../../Entities/Camera2D.h"

#include "../../Config/GlobalConfiguration.h"
#include "../../GameInstance.h"

#include "../../Gui/Label.h"
#include "../../Gui/Button.h"

#include "../../Scene/Scene.h"

#include "Snake.h"
#include "Food.h"
#include "ScoreBoard.h"
#include "Wall.h"
#include "../../Renderer/ImguiRenderer.h"
#include "../../Renderer/SpriteRenderer.h"
#include "../../Renderer/TextRenderer.h"


int Score;
Camera2D* camera;

// ---
SnakeGame::SnakeGame()
{
	
}

SnakeGame::~SnakeGame()
{
}

// ---public
int SnakeGame::Initialize()
{

	GameInstance::Initialize();

	// Load Game Instance Config
	// LoadGameConfig("config path");
	// 
	
	// Pre Load Resource
	g_pResourceManager->LoadTexture("Assets/Textures/awesomeface.png", "face");
	g_pResourceManager->LoadTexture("Assets/Textures/awesomeface_transparent.png", "face_transparent");
	g_pResourceManager->LoadTexture("Assets/Textures/dialogbox005.png", "dialogbox");
	g_pResourceManager->LoadTexture("Assets/Textures/Background.jpg", "background");
	g_pResourceManager->LoadTexture("Assets/Textures/girl001.jpg", "character");
	g_pResourceManager->LoadTexture("Assets/Textures/Blank.png", "blank");
	g_pResourceManager->LoadTexture("Assets/Textures/block.png", "block");
	g_pResourceManager->LoadTexture("Assets/Textures/ReadyScene.png", "ReadyScene");
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

	std::shared_ptr<Scene> ReadyScene = std::make_shared<Scene>("ReadyScene");
	std::shared_ptr<Scene> Level0 = std::make_shared<Scene>("Level0");

	RenderableObject* Level0BG = new RenderableObject("dialogbox", 0, 0, 800, 600);
	Snake* snake = new Snake("face_transparent", 0, 0, 50);
	Food* food = new Food("blank");
	ScoreBoard* scoreBoard = new ScoreBoard;
	Label* fpsLabel = new Label(L"FPS:", 0.0f, 50.0f, 1.0f); 
	Button* button = new Button("Restart", { 150.0f, 350.0f }, { 150.f, 50.f });
	Button* button2 = new Button("Return to title", { 450.0f, 350.0f }, { 150.f, 50.f });


	Wall* wall = new Wall("block");

	RenderableObject* ReadySceneObject = new RenderableObject("ReadyScene", 0, 0, 800, 600);
	ReadyScene->AddGameObject("ReadySceneObject", ReadySceneObject);
	Label* StartLabel = new Label(L"Please press any key to start", 50.0f, 400.0f, 1.0f);
	ReadyScene->AddGameObject("StartLabel", StartLabel);

	Level0->AddGameObject("Level0BG", Level0BG);
	Level0->AddGameObject("snake", snake);
	Level0->AddGameObject("food", food);
	Level0->AddGameObject("scoreBoard", scoreBoard);
	Level0->AddGameObject("fpsLabel", fpsLabel);
	Level0->AddGameObject("button", button);
	Level0->AddGameObject("button2", button2);

	g_pSceneManager->AddScene("ReadyScene", ReadyScene);
	g_pSceneManager->AddScene("Level0", Level0);

	Ready();
	return 0;
}

int SnakeGame::Tick()
{
	return 0;
}

int SnakeGame::Release()
{
	return 0;
}

// handle event
void SnakeGame::ProcessInput()
{
	if (IsRunning())
	{
		if (g_pInputManager->IsKeyPressed("Enter"))
		{
			Pause();
		}
		if (g_pInputManager->IsKeyPressed("Esc"))
		{
			Stop();
		}
		for (auto obj : mCurrentScene->GetSceneObjects())
		{
			if (obj.second)
			{
				obj.second->OnKeyPressed();
			}
		}
	}
	else
	{
		if (g_pInputManager->IsKeyPressed("Enter"))
		{
			Start();
		}
	}
}

void SnakeGame::Render()
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

void SnakeGame::Update(float elapsedTime)
{
	//player->Update(elapsedTime);
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

void SnakeGame::DetectCollide()
{
	if (!IsRunning()) {
		return;
	}
	if (mCurrentScene->GetGameObject("snake") == nullptr)
	{
		return;
	}
	if (mCurrentScene->GetGameObject("food" ) == nullptr)
	{
		return;
	}

	if (mCurrentScene->GetGameObject("snake")->IsCollide(mCurrentScene->GetGameObject("food")))
	{
		AddPoint();
	}

	// for(const auto& obj : mCurrentScene->GetSceneObjects())
	// {
	// 	if (mCurrentScene->GetGameObject("snake")->IsCollide(obj.second))
	// 	{
	// 		
	// 	}
	// 	
	// }
	
}


// change game state
bool SnakeGame::IsRunning()
{
	return g_pStateManager->IsGameRunning();
}

int SnakeGame::Stop()
{
	g_pStateManager->GameOver();
	return 0;
}

int SnakeGame::Pause()
{
	g_pStateManager->GamePause();
	return 0;
}

int SnakeGame::Start()
{
	if (g_pStateManager->IsGameOver())
	{
		mCurrentScene = g_pSceneManager->LoadScene("Level0");
	}
	
	g_pStateManager->GameStart();
	return 0;
}

void SnakeGame::AddPoint()
{
	auto scoreBoard = dynamic_cast<ScoreBoard*>(mCurrentScene->GetGameObject("scoreBoard"));
	if (scoreBoard != nullptr)
	{
		scoreBoard->AddPoint();
	}
}

void SnakeGame::Ready()
{
	mCurrentScene = g_pSceneManager->LoadScene("ReadyScene");
}