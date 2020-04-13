#include "Application.h"
#include <GLAD/glad.h>
#include "Managers/InputManager.h"
#include "Game/GlobalConfiguration.h"
#include "Game/Snake/SnakeGame.h"

int Application::Initialize()
{

	auto config = Configuration::Get();
	config->Load("Assets/Conf/gConfig.xml");

	sf::ContextSettings settings;
	settings.depthBits = 32;
	settings.stencilBits = 8;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	mWindow = new sf::RenderWindow(sf::VideoMode(config->GetWidth(), config->GetHeight()), "OpenGL with SFML", sf::Style::Default, settings);
	mGame = new SnakeGame;
	mGame->Initialize();

	return 0;
}

int Application::Run()
{
	sf::Clock clock;
	float elapsedTime = clock.getElapsedTime().asSeconds();
	while (mWindow->isOpen()) {
		ProcessEvent();
		elapsedTime = clock.restart().asSeconds();
		mGame->Update(elapsedTime);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		mGame->Render();

		mWindow->display();
	}
	return 0;
}

int Application::Release()
{
	mGame->Release();
	delete mWindow;
	return 0;
}

int Application::ProcessEvent()
{
	sf::Event event;
	while (mWindow->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			mWindow->close();
			return 0;
		}
		if (event.type == sf::Event::EventType::KeyPressed) {
			switch (event.key.code)
			{
			case sf::Keyboard::Key::Escape:
				mGame->Stop();
				break;
			case sf::Keyboard::Key::Enter:
				mGame->Start();
				break;
			case sf::Keyboard::Key::Space:
				mGame->Pause();
				break;
			default:
				InputManager::Get()->KeyPressed(event.key.code);
				break;
			}
		}
		if (event.type == sf::Event::EventType::KeyReleased) {
			InputManager::Get()->KeyRelease(event.key.code);
		}
		if (event.type == sf::Event::Resized)
		{
			glViewport(0, 0, event.size.width, event.size.height);
		}
	}

	mGame->ProcessInput();
	return 0;
}
