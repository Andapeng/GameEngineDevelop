#include "SnakeGame.h"
#include "../../Managers/Managers.h"

#include <GLAD/glad.h>
#include "../../RHI/Shader.h"
#include "../../RHI/Texture.h"
#include "../../RHI/Character.h"

#include "../../Math/Math.h"

#include "../../Entities/GameObject.h"
#include "../../Entities/RenderableObject.h"
#include "../../Entities/Player.h"
#include "../../Entities/Camera2D.h"

#include "Snake.h"
#include "Food.h"
#include "Wall.h"

#include <iostream>
#include "../GlobalConfiguration.h"
#include "ScoreBoard.h"

int Score;
Camera2D* camera;

// ---
SnakeGame::SnakeGame()
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

	Snake*  snake = new Snake("face_transparent", 0, 0, 50);
	Food* food = new Food("blank");
	ScoreBoard* scoreBoard = new ScoreBoard;

	AddGameObject("snake", snake);
	AddGameObject("food", food);
	AddGameObject("scoreBoard", scoreBoard);

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


// ---private

// handle event
void SnakeGame::ProcessInput()
{
	if (IsRunning())
	{
		for (auto obj : m_GameObjectsMap)
		{
			obj.second->OnKeyPressed();
		}
	}
}


void SnakeGame::Render()
{
	if (!g_pStateManager->IsGameOver()) 
	{
		for (auto obj : m_GameObjectsMap)
		{
			obj.second->OnRender();
		}	
	}
}

void SnakeGame::Update(float elapsedTime)
{
	//player->Update(elapsedTime);
	if (IsRunning()) {
		for (auto obj : m_GameObjectsMap)
		{
			obj.second->Update(elapsedTime);
		}
	}
}

void SnakeGame::DetectCollide()
{
	// snake for all wall
	//		checkcollide return hitInfo
	//		if hitInfo.isCollide is true
	//		snake.OnCollide and wall[n].OnCollide
	// snake and food
	//		checkcollide return hitInfo
	//		if hitInfo.isCollide is true
	//		snake.OnCollide and food.OnCollide

	if (GetGameObject("snake")->IsCollide(GetGameObject("food")))
	{
		auto scoreBoard = dynamic_cast<ScoreBoard*>(GetGameObject("scoreBoard"));
		if (scoreBoard != nullptr)
		{
			scoreBoard->AddPoint();
		}
	}
}


// change game state
bool SnakeGame::IsRunning()
{
	return g_pStateManager->IsGameRuning();
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
	g_pStateManager->GameStart();
	return 0;
}

bool SnakeGame::AddGameObject(std::string objectName, GameObject* gameObject)
{
	m_GameObjectsMap[objectName] = gameObject;
	return true;
}
