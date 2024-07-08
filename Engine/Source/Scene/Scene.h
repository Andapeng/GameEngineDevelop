#pragma once
#include <map>
#include <string>
#include <vector>

class GameObject;

class Scene
{
public:
	Scene();
	Scene(const std::string& sceneName) { m_sceneName = sceneName; }
	~Scene();

	void SetName(const std::string& sceneName) { m_sceneName = sceneName; }

	bool AddGameObject(std::string objectName, GameObject* gameObject);
	GameObject* GetGameObject(const std::string& objectName) { return m_GameObjectsMap[objectName]; }
private:
	std::map<std::string, GameObject*> m_GameObjectsMap;
	std::string m_sceneName;
};
