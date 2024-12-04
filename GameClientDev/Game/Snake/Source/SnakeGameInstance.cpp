#include "SnakeGameInstance.h"

#include "Managers/Managers.h"

#include "RHI/Shader.h"
#include "RHI/Texture.h"
#include "RHI/Character.h"

#include "Entities/GameObject.h"
#include "Entities/Camera2D.h"

#include "Config/GlobalConfiguration.h"
#include "GameInstance.h"

#include "Gui/Label.h"

#include "Snake.h"
#include "Food.h"
#include "ScoreBoard.h"
#include "Wall.h"

#include "Scene/Scene.h"


int Score;
Camera2D* camera;

// ---
SnakeGameInstance::SnakeGameInstance()
{

}

SnakeGameInstance::~SnakeGameInstance()
{
}

// ---public
int SnakeGameInstance::Initialize()
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

int SnakeGameInstance::Tick()
{
	ProcessInput();
	Render();

	return 0;
}

int SnakeGameInstance::Release()
{
	for (auto obj : m_GameObjectsMap)
	{
		delete obj.second;
	}
	m_GameObjectsMap.clear();

	return 0;
}

// handle event
void SnakeGameInstance::ProcessInput()
{
	if (IsRunning())
	{
		for (auto obj : m_GameObjectsMap)
		{
			if (obj.second)
			{
				obj.second->OnKeyPressed();
			}
		}
	}
}


void SnakeGameInstance::Render()
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
	}
}

void SnakeGameInstance::Update(float elapsedTime)
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

void SnakeGameInstance::DetectCollide()
{
	if (GetGameObject("snake") == nullptr)
	{
		return;
	}
	if (GetGameObject("food") == nullptr)
	{
		return;
	}

	if (GetGameObject("snake")->IsCollide(GetGameObject("food")))
	{

		AddPoint();
	}

	// if (IsWall(gameObject.second))
	// {
	// 	Stop();
	// 	break;
	// }

}


// change game state
bool SnakeGameInstance::IsRunning()
{
	return g_pStateManager->IsGameRunning();
}

int SnakeGameInstance::Stop()
{
	for (auto& obj : m_GameObjectsMap)
	{
		delete obj.second;
	}
	m_GameObjectsMap.clear();
	g_pStateManager->GameOver();
	return 0;
}

int SnakeGameInstance::Pause()
{
	g_pStateManager->GamePause();
	return 0;
}

int SnakeGameInstance::Start()
{
	if (g_pStateManager->IsGameOver())
	{
		Snake* snake = new Snake("face_transparent", 0, 0, 50);
		Food* food = new Food("blank");
		ScoreBoard* scoreBoard = new ScoreBoard;
		Label* fpsLabel = new Label(L"FPS:", 0.0f, 50.0f, 1.0f);
		Wall* wall = new Wall("blank");

		AddGameObject("snake", snake);
		AddGameObject("food", food);
		AddGameObject("scoreBoard", scoreBoard);
		AddGameObject("fpsLabel", fpsLabel);
		// AddGameObject("wall", wall);
	}

	g_pStateManager->GameStart();
}

void SnakeGameInstance::AddPoint()
{
	auto scoreBoard = dynamic_cast<ScoreBoard*>(GetGameObject("scoreBoard"));
	if (scoreBoard != nullptr)
	{
		scoreBoard->AddPoint();
	}
}

bool SnakeGameInstance::AddGameObject(const std::string& objectName, GameObject* gameObject)
{
	m_GameObjectsMap[objectName] = gameObject;
	return true;
}

bool SnakeGameInstance::AddScene(const std::string& sceneName, Scene* scene)
{
	m_sceneMap[sceneName] = scene;
	return true;
}

Scene* SnakeGameInstance::GetScene(const std::string& sceneName)
{
	return m_sceneMap[sceneName];
}
