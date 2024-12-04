#pragma once
#include <memory>
#include <string>
#include <map>
#include "../../GameInstance.h"

class Scene;
class GameObject;

class SnakeGame : public GameInstance
{

public:
	
	SnakeGame();
	~SnakeGame() override;

	// runtime
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
	void AddPoint();

	void Ready();

private:
	std::shared_ptr<Scene> mCurrentScene;

};