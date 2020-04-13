#pragma once
#include <SFML/Graphics.hpp>
#include "Game/GameInstance.h"

class Application
{
public:
	int Initialize();
	int Run();
	int Release();
protected:
	int ProcessEvent();


private:
	GameInstance* mGame;
	sf::RenderWindow* mWindow;
};