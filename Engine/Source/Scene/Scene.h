#pragma once
#include <map>
#include <string>

class GameObject;
class Scene
{
public:
	Scene();
	Scene(const std::string& sceneName) { m_sceneName = sceneName; }
	~Scene();

	void Release();

	void SetName(const std::string& sceneName) { m_sceneName = sceneName; }

	bool AddGameObject(const std::string& objectName, GameObject* gameObject);
	GameObject* GetGameObject(const std::string& objectName) { return m_GameObjectsMap[objectName]; }
	std::map<std::string, GameObject*> GetSceneObjects() { return m_GameObjectsMap; }
private:
	std::map<std::string, GameObject*> m_GameObjectsMap;
	std::string m_sceneName;
};
