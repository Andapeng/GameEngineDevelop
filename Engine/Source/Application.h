#pragma once
#include "GameInstance.h"
#include "Platform/Window.h"

#include <memory>

class Application
{
public:
	int Initialize(std::shared_ptr<GameInstance> InGameInstance);
	int Run();
	int Release();
protected:
	void ProcessEvent();


private:
        std::shared_ptr<GameInstance> mGame = nullptr;
	std::unique_ptr<sadp::Window> mWindow = nullptr;
};