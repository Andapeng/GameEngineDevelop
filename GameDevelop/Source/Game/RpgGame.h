#pragma once
#include <SFML/Graphics.hpp>

class RpgGame 
{

public:
	
	RpgGame();
	int Initialize();
	int Tick();
	int Release();

private:
	

	// manage event
	void PollEvent();
	
	// manage render
	void Render();

	// manage game state
	bool IsRunning();
	int GameClose();
	int GameStart();

	enum class GameState
	{
		running = 0,
		closed = 1,
		paused = 2
	};
	sf::RenderWindow* mWindow;
	
};