#pragma once
#include <string>
#include <map>
#include "GameInstance.h"

class Scene;
class GameObject;

class SnakeGameInstance : public GameInstance
{

public:

	SnakeGameInstance();
	~SnakeGameInstance() override;

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
	bool IsFood(GameObject* gameObject);
	bool IsWall(GameObject* gameObject);

private:
	bool AddGameObject(const std::string& objectName, GameObject* gameObject);
	GameObject* GetGameObject(const std::string& objectName) { return m_GameObjectsMap[objectName]; }
	bool AddScene(const std::string& sceneName, Scene* scene);
	Scene* GetScene(const std::string& sceneName);
private:
	std::map<std::string, GameObject*> m_GameObjectsMap;
	std::map<std::string, Scene*> m_sceneMap;
};