#pragma once
#include <map>
#include <memory>
#include <string>

class GameObject;
class Scene
{
public:
	Scene();
	Scene(const std::string& sceneName) { mSceneName = sceneName; }
	~Scene();

	void Release();

	void SetName(const std::string& sceneName) { mSceneName = sceneName; }

	bool AddGameObject(const std::string& objectName, std::shared_ptr<GameObject> gameObject);
	std::shared_ptr<GameObject> GetGameObject(const std::string& objectName);
	std::map<std::string, std::shared_ptr<GameObject>> GetSceneObjects() { return mGameObjectsMap; }
private:
	std::map<std::string, std::shared_ptr<GameObject>> mGameObjectsMap;
	std::string mSceneName;
};
