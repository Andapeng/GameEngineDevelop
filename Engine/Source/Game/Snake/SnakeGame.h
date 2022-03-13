#pragma once
#include <SFML/Graphics.hpp>
#include "../GameInstance.h"

class GameObject;

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
	bool AddGameObject(std::string objectName, GameObject* gameObject);
	GameObject* GetGameObject(std::string objectName) { return m_GameObjectsMap[objectName]; }
private:
	std::map<std::string, GameObject*> m_GameObjectsMap;
};