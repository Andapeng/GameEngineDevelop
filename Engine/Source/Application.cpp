#include "Application.h"
#include "Config/GlobalConfiguration.h"
#include "Managers/Managers.h"
#include "Misc/GameTimer.h"
#include "imgui-sfml/imgui-SFML.h"
int Application::Initialize(GameInstance* InGameInstance)
{

	auto config = Configuration::Get();
	config->Load("Assets/Conf/gConfig.xml");

	g_pWindowManager = WindowManager::Get();
	
	mWindow = new sadp::Window;
	mWindow->Create();
	g_pWindowManager->RegisterWindow(mWindow, true);

	g_pStateManager = StateManager::Get();
	g_pResourceManager = ResourceManager::Get();
	g_pGraphicsManager = GraphicsManager::Get();
	g_pFontManager = FontManager::Get();
	g_pInputManager = InputManager::Get();
	g_pPhysicsManager = PhysicsManager::Get();
	g_pNetworkManager = NetworkManager::Get();
	g_pAudioManager = AudioManager::Get();
	g_pStatisticsManager = StatisticsManager::Get();
	g_pSceneManager = SceneManager::Get();

	g_pWindowManager->Initialize();
	g_pGraphicsManager->Initialize();
	g_pFontManager->Initialize();
	g_pInputManager->Initialize();
	g_pPhysicsManager->Initialize();
	g_pNetworkManager->Initialize();
	g_pAudioManager->Initialize();
	g_pStatisticsManager->Initialize();
	g_pSceneManager->Initialize();


	mGame = InGameInstance;
	mGame->Initialize();

	return 0;
}

int Application::Run()
{
	GameTimer g_GameTimer;
	float elapsedTime = g_GameTimer.Start();
	while (mWindow->IsOpen()) {

		ProcessEvent();

		elapsedTime = g_GameTimer.GetElapsedTime();
		mGame->Update(elapsedTime);
		mWindow->Update(elapsedTime);
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

	g_pSceneManager->Release();
	g_pStatisticsManager->Release();
	g_pAudioManager->Release();
	g_pFontManager->Release();
	g_pGraphicsManager->Release();
	g_pResourceManager->Release();
	g_pInputManager->Release();
	g_pPhysicsManager->Release();
	g_pNetworkManager->Release();
	g_pGraphicsManager->Release();
	g_pWindowManager->Release();

	return 0;
}

void Application::ProcessEvent()
{
	mWindow->ProcessEvent();
	mGame->ProcessInput();
}


