#pragma once
#include "GameInstance.h"
#include "Platform/Window.h"

#include <memory>

class Application
{
public:
	int Initialize(GameInstance* InGameInstance);
	int Run();
	int Release();
protected:
	void ProcessEvent();


private:
	GameInstance* mGame = nullptr;
//	sf::RenderWindow* mWindow;
	std::unique_ptr<sadp::Window> mWindow = nullptr;
};