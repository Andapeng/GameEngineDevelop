#pragma once
#include <map>
#include <memory>
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

	bool AddGameObject(const std::string& objectName, std::shared_ptr<GameObject> gameObject);
	std::shared_ptr<GameObject> GetGameObject(const std::string& objectName);
	std::map<std::string, std::shared_ptr<GameObject>> GetSceneObjects() { return m_GameObjectsMap; }
private:
	std::map<std::string, std::shared_ptr<GameObject>> m_GameObjectsMap;
	std::string m_sceneName;
};
