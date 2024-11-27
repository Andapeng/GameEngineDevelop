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


#include "Snake.h"
#include "Food.h"

#include <iostream>
#include "ScoreBoard.h"
#include "../../Scene/Scene.h"
#include "Wall.h"


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
	g_pResourceManager->LoadTexture("Assets/Textures/Background2.jpg", "background");
	g_pResourceManager->LoadTexture("Assets/Textures/girl001.jpg", "character");
	g_pResourceManager->LoadTexture("Assets/Textures/Blank.png", "blank");
	g_pResourceManager->LoadShader("Assets/Shaders/texture.vertex", "Assets/Shaders/texture.fragment", "texture_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/sprite.vertex", "Assets/Shaders/sprite.fragment", "sprite_shader");
	g_pResourceManager->LoadShader("Assets/Shaders/text.vertex", "Assets/Shaders/text.fragment", "text_shader");
	g_pFontManager->LoadFont("Assets/Fonts/simsun.ttc");

	auto config = Configuration::Get();
	camera = new Camera2D(config->GetWidth(), config->GetHeight());

	// Set Shader Uniform
	g_pResourceManager->GetShader("sprite_shader").Use()->SetInt("texture1", 0);
	g_pResourceManager->GetShader("sprite_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("text_shader").Use()->SetInt("text", 0);
	g_pResourceManager->GetShader("text_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("texture_shader").Use()->SetInt("texture1", 0);

	Scene readyScene("readyScene");
	//Sprite background("background");

	this->Start();
	return 0;
}

int SnakeGame::Tick()
{
	ProcessInput();	
	Render();

	return 0;
}

int SnakeGame::Release()
{	
	for (auto obj : m_GameObjectsMap)
	{
		delete obj.second;
	}
	m_GameObjectsMap.clear();

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
		for (auto obj : m_GameObjectsMap)
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
	if (!g_pStateManager->IsGameOver()) 
	{
		for (auto obj : m_GameObjectsMap)
		{
			if (obj.second)
			{
				obj.second->OnRender();
			}
		}
		g_pGraphicsManager->Tick();
	}
}

void SnakeGame::Update(float elapsedTime)
{
	//player->Update(elapsedTime);
	if (IsRunning()) {
		for (auto obj : m_GameObjectsMap)
		{
			if (obj.second)
			{
				obj.second->Update(elapsedTime);
			}
		}

		if (const auto fpsLabel = dynamic_cast<Label*>(GetGameObject("fpsLabel")))
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
	if (GetGameObject("snake") == nullptr)
	{
		return;
	}
	if (GetGameObject("food" ) == nullptr)
	{
		return;
	}

	for (auto& gameObject : m_GameObjectsMap)
	{
		if(GetGameObject("snake")->IsCollide(gameObject.second))
		{
			if (IsFood(gameObject.second))
			{
				AddPoint();
			}

			// if (IsWall(gameObject.second))
			// {
			// 	Stop();
			// 	break;
			// }
		}
	}
	
}


// change game state
bool SnakeGame::IsRunning()
{
	return g_pStateManager->IsGameRunning();
}

int SnakeGame::Stop()
{
	for (auto& obj : m_GameObjectsMap)
	{
		delete obj.second;
	}
	m_GameObjectsMap.clear();
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
		Snake* snake = new Snake("face_transparent", 0, 0, 50);
		Food* food = new Food("blank");
		ScoreBoard* scoreBoard = new ScoreBoard;
		Label* fpsLabel = new Label(L"FPS:", 0.0f, 50.0f, 1.0f);
		Button* button = new Button();
		Wall* wall = new Wall("blank");
	
		AddGameObject("snake", snake);
		AddGameObject("food", food);
		AddGameObject("scoreBoard", scoreBoard);
		AddGameObject("fpsLabel", fpsLabel);
		AddGameObject("button", button);
		// AddGameObject("wall", wall);
	}
	
	g_pStateManager->GameStart();
	return 0;
}

void SnakeGame::AddPoint()
{
	auto scoreBoard = dynamic_cast<ScoreBoard*>(GetGameObject("scoreBoard"));
	if (scoreBoard != nullptr)
	{
		scoreBoard->AddPoint();
	}
}

bool SnakeGame::IsFood(GameObject* gameObject)
{
	Food* food = dynamic_cast<Food*>(gameObject);
	if (food != nullptr)
	{
		return true;
	}
	return false;
}

bool SnakeGame::IsWall(GameObject* gameObject)
{
	Wall* wall = dynamic_cast<Wall*>(gameObject);
	if (wall != nullptr)
	{
		return true;
	}
	return false;
}

bool SnakeGame::AddGameObject(const std::string& objectName, GameObject* gameObject)
{
	m_GameObjectsMap[objectName] = gameObject;
	return true;
}

bool SnakeGame::AddScene(const std::string& sceneName, Scene* scene)
{
	m_sceneMap[sceneName] = scene;
	return true;
}

Scene* SnakeGame::GetScene(const std::string& sceneName)
{
	return m_sceneMap[sceneName];
}
