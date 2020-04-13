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
#include "../../Network/NetworkClient.h"

Snake* snake;
Food* food;
Wall* wall;

NetworkClient client;
int Score;
Camera2D* camera;
// ---
SnakeGame::SnakeGame()
{
	
}

// ---public
int SnakeGame::Initialize()
{

	// Managers Initializing
	g_pStateManager = StateManager::Get();
	g_pResourceManager = ResourceManager::Get();
	g_pGraphicsManager = GraphicsManager::Get();
	g_pFontManager = FontManager::Get();
	g_pInputManager = InputManager::Get();
	g_pPhysicsManager = PhysicsManager::Get();
	g_pAudioManager = AudioManager::Get();

	g_pGraphicsManager->Initialize();
	g_pFontManager->Initialize();
	g_pInputManager->Initialize();
	g_pPhysicsManager->Initialize();
	g_pAudioManager->Initialize();

	client.Initialize();
	client.Send();

	// Pre Load Resource
	g_pResourceManager->LoadTexture("Assets/Textures/awesomeface.png", "face");
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

	//Eigen::Matrix4f projection = Ortho(0.0f, static_cast<float>(config->GetWidth()), static_cast<float>(config->GetHeight()), 0.0f, -1.0f, 1.0f);
	//std::cout << "Projection1 Matrix: \n" << camera->GetProjectMatrix() << std::endl;
	

	// Set Shader Uniform
	g_pResourceManager->GetShader("sprite_shader").Use()->SetInt("texture1", 0);
	g_pResourceManager->GetShader("sprite_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("text_shader").Use()->SetInt("text", 0);
	g_pResourceManager->GetShader("text_shader").SetMatrix4f("projection", camera->GetProjectMatrix());

	g_pResourceManager->GetShader("texture_shader").Use()->SetInt("texture1", 0);

	snake = new Snake("blank", 0, 0, 50);
	food = new Food("blank");
	wall = new Wall("blank");
	//MusicPlayer.openFromFile("Assets/Music/Start1.ogg");
	//MusicPlayer.play();

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
	delete wall;
	delete food;
	delete snake;
	
	g_pFontManager->Release();
	g_pGraphicsManager->Release();
	g_pResourceManager->Release();
	g_pInputManager->Release();
	g_pPhysicsManager->Release();

	return 0;
}


// ---private

// handle event
void SnakeGame::ProcessInput()
{
	//player->OnKeyPressed();
	if (IsRunning())
	{
		snake->OnKeyPressed();
	}
}


void SnakeGame::Render()
{
	//player->OnRender(spriteRenderer);
	if (!g_pStateManager->IsGameOver()) 
	{
		snake->OnRender();
		food->OnRender();
		wall->OnRender();
	}
}

void SnakeGame::Update(float elapsedTime)
{
	//player->Update(elapsedTime);
	if (IsRunning()) {
		snake->Update(elapsedTime);
		snake->eatFood(*food);
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
