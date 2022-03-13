#include "Breakout.h"
#include "../../Managers/Managers.h"

#include <GLAD/glad.h>
#include "../../RHI/Shader.h"
#include "../../RHI/Texture.h"
#include "../../RHI/Character.h"

#include "../../Math/Math.h"

#include "../../Entities/GameObject.h"
#include "../../Entities/RenderableObject.h"
#include "../../Entities/Player.h"

#include <iostream>
#include "../GlobalConfiguration.h"
#include "../../Network/NetworkClient.h"


int Breakout::Initialize()
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

	return 0;
}

int Breakout::Tick()
{
	return 0;
}

int Breakout::Release()
{
	g_pAudioManager->Release();
	g_pPhysicsManager->Release();
	g_pInputManager->Release();
	g_pFontManager->Release();
	g_pGraphicsManager->Release();

	return 0;
}

void Breakout::ProcessInput()
{
}

void Breakout::Render()
{
}

void Breakout::Update(float elapsedTime)
{
}

void Breakout::DetectCollide()
{
}
