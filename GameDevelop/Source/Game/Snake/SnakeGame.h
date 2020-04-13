#pragma once
#include <SFML/Graphics.hpp>
#include "../GameInstance.h"

class SnakeGame : public GameInstance
{

public:
	
	SnakeGame();
	virtual int Initialize() override;
	virtual int Tick() override;
	virtual int Release() override;

	// manage event
	void ProcessInput() override;

	// manage render
	void Render() override;

	// game state update
	void Update(float elapsedTime) override;

	// manage physics
	void DetectCollide() override;

	// manage game state
	bool IsRunning();
	int Stop() override;
	int Pause() override;
	int Start() override;
private:
	
};