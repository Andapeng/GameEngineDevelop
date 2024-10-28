#include "Application.h"
#include "Config/GlobalConfiguration.h"
#include "Managers/StatisticsManager.h"

int Application::Initialize(GameInstance* InGameInstance)
{

	auto config = Configuration::Get();
	config->Load("Assets/Conf/gConfig.xml");

	sf::ContextSettings settings;
	settings.depthBits = config->GetDepthBits();
	settings.stencilBits = config->GetStencilBits();
	settings.majorVersion = config->GetMajorVersion();
	settings.minorVersion = config->GetMinorVersion();

	mWindow = new sadp::Window;
	mWindow->Create();
	mGame = InGameInstance;
	mGame->Initialize();

	return 0;
}

int Application::Run()
{
	sf::Clock clock;
	float elapsedTime = clock.getElapsedTime().asSeconds();
	while (mWindow->IsOpen()) {

		ProcessEvent();

		elapsedTime = clock.restart().asSeconds();
		mGame->Update(elapsedTime);
		g_pStatisticsManager->UpdateFPS(elapsedTime);

		mGame->DetectCollide();

		mWindow->OnRenderBefore();
		mGame->Render();
		mWindow->Show();
	}
	return 0;
}

int Application::Release()
{
	mGame->Release();
	delete mWindow;
	return 0;
}

void Application::ProcessEvent()
{
	mWindow->ProcessEvent();
	mGame->ProcessInput();
}


