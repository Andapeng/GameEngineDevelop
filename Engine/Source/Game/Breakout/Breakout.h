#pragma once
#include <memory>
#include <vector>

#include "../../GameInstance.h"
class GameObject;
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

	void previousLevel();
	void nextLevel();
	void resetLevel();
	void resetPlayer();
	void showMenu(bool bIsShow);
	void showGameOver(bool bIsShow);

	std::shared_ptr<Scene> mCurrentScene;
	Camera2D* camera;
	int mLevel = 0;

	std::vector<std::shared_ptr<GameObject>> mGameLevels;
	const int MAX_LEVEL = 3;
	const int MAX_LIVES = 3;
	int mLives = MAX_LIVES;
};
