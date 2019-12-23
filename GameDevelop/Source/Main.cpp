// Main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "GraphicsManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameInstance.h"
ResourceManager* g_pResourceManager = new ResourceManager();
GraphicsManager* g_pGraphicsManager = new GraphicsManager();
InputManager* g_pInputManager = new InputManager();
GameInstance* Game = new GameInstance();
int main()
{
	bool isResourceManagerInit = g_pResourceManager->Initialize();
	if (!isResourceManagerInit)
	{
		// ...
		return 0;
	}
	bool isGraphicsInit = g_pGraphicsManager->Initialize();
	if (!isGraphicsInit) {
		// ...
		return 0;
	}
	bool isInputInit = g_pInputManager->Initialize();
	if (!isInputInit) {
		// ...
		return 0;
	}

	while (1)
	{
		if (Game->isExit())
		{
			g_pGraphicsManager->Tick();
			g_pInputManager->Tick();
			return 0;
		}
	}
	
	g_pGraphicsManager->Release();
	g_pInputManager->Release();
}
