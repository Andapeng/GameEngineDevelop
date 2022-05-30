#include "GameInstance.h"
#include "../Managers/Managers.h"
int GameInstance::Initialize()
{
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
	return 0;
}

int GameInstance::Tick()
{
	return 0;
}

int GameInstance::Release()
{
	g_pAudioManager->Release();
	g_pFontManager->Release();
	g_pGraphicsManager->Release();
	g_pResourceManager->Release();
	g_pInputManager->Release();
	g_pPhysicsManager->Release();
	return 0;
}

void GameInstance::ProcessInput()
{
}

void GameInstance::Render()
{
}

void GameInstance::Update(float elapsedTime)
{
}

void GameInstance::DetectCollide()
{
}

int GameInstance::Start()
{
	return 0;
}

int GameInstance::Pause()
{
	return 0;
}

int GameInstance::Stop()
{
	return 0;
}
