#pragma once
#include <memory>

#include "../../GameInstance.h"
class Camera2D;
class Scene;

class Breakout : public GameInstance
{
	virtual int Initialize() override;
	virtual int Tick() override;
	virtual int Release() override;

	// manage event
	virtual void ProcessInput() override;

	// manage render
	virtual void Render() override;

	// game state update
	virtual void Update(float elapsedTime) override;

	// manage physics
	virtual void DetectCollide() override;

	// manage game state
	bool IsRunning();
	int Stop() override;
	int Pause() override;
	int Start() override;
private:
	std::shared_ptr<Scene> mCurrentScene;
	Camera2D* camera;
};
