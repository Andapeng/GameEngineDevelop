#pragma once
#include "GameInstance.h"
#include "Platform/Window.h"

class Application
{
public:
	int Initialize(GameInstance* InGameInstance);
	int Run();
	int Release();
protected:
	void ProcessEvent();


private:
	GameInstance* mGame;
//	sf::RenderWindow* mWindow;
	sadp::Window* mWindow;
};