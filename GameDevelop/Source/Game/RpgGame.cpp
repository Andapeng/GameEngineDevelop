#include "RpgGame.h"
#include <SFML/Graphics.hpp>
#include "../Managers/StateManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/FontManager.h"

#include <GLAD/glad.h>
#include "../RHI/Shader.h"
#include "../RHI/Renderer.h"
#include "../RHI/Texture.h"

#include <iostream>
#include "GlobalConfiguration.h"
StateManager* g_pStateManager;
ResourceManager* g_pResourceManager;
GraphicsManager* g_pGraphicsManager;
FontManager* g_pFontManager;
Renderer* renderer;
// ---
RpgGame::RpgGame()
	:mWindow(nullptr)
{
	
}

// ---public
int RpgGame::Initialize()
{

	

	sf::ContextSettings settings;
	settings.depthBits = 32;
	settings.stencilBits = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 5;
	
	mWindow = new sf::RenderWindow(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "OpenGL with SFML", sf::Style::Default, settings);


	// Managers Initializing
	g_pStateManager = StateManager::Get();
	g_pResourceManager = ResourceManager::Get();
	g_pGraphicsManager = GraphicsManager::Get();
	g_pFontManager = FontManager::Get();
	
	g_pGraphicsManager->Initialize();
	g_pFontManager->Initialize();
	
	// Pre Load Resource
	g_pResourceManager->LoadTexture("Assets/Textures/container.jpg", "dialogbox");
	g_pResourceManager->LoadShader("Assets/Shaders/texture.vertex", "Assets/Shaders/texture.fragment", "texture_shader");
	//g_pResourceManager->LoadShader("Assets/Shaders/sprite.vertex", "Assets/Shaders/sprite.fragment", "sprite_shader");
	g_pFontManager->LoadFont("Assets/Fonts/simsun.ttc");

	Eigen::Matrix4f projection = Ortho(0.0f, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0.0f, -1.0f, 1.0f);
	std::cout << "Projection Matrix: \n" << projection << std::endl;
	
	// Set Shader Uniform
	//g_pResourceManager->GetShader("sprite_shader").Use()->SetInt("image", 0);
	//g_pResourceManager->GetShader("sprite_shader").SetMatrix4f("projection", projection);

	g_pResourceManager->GetShader("texture_shader").Use()->SetInt("texture1", 0);

	renderer = new Renderer();
	renderer->Initialize();
	return 0;
}

int RpgGame::Tick()
{


	GameStart();

	while (mWindow->isOpen()) {
		
		PollEvent();
		Render();

		
		mWindow->display();
	}


	return 0;
}

int RpgGame::Release()
{
	renderer->Release();
	g_pFontManager->Release();
	g_pGraphicsManager->Release();
	g_pResourceManager->Release();

	delete mWindow;
	return 0;
}


// ---private

// handle event
void RpgGame::PollEvent()
{
	sf::Event event;
	while (mWindow->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mWindow->close();
			return;
		}
		if (event.type == sf::Event::EventType::KeyPressed) {
			switch (event.key.code)
			{
			case sf::Keyboard::Key::Escape:
				GameClose();
				break;
			case sf::Keyboard::Key::Enter:
				GameStart();
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
		}
	}
}


void RpgGame::Render()
{
	//renderer->RenderSprite(g_pResourceManager->GetTexture("dialogbox"), Eigen::Vector2f(200, 200), Eigen::Vector2f(200, 200), 0, Eigen::Vector3f(1.0f, 1.0f, 1.0f));
	renderer->TestRender();
}


// change game state
bool RpgGame::IsRunning()
{
	return g_pStateManager->IsGameRuning();
}

int RpgGame::GameClose()
{
	g_pStateManager->GameClose();
	return 0;
}

int RpgGame::GameStart()
{
	g_pStateManager->GameStart();
	return 0;
}
