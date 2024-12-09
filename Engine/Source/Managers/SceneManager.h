#pragma once
#include <memory>
#include <string>
#include <map>

#include "IManager.h"
class Scene;
class GameObject;
class SceneManager : public IManager
{
public:
	virtual ~SceneManager();

	virtual int Initialize() override;
	virtual void Tick() override;
	virtual void Release() override;

	static SceneManager* Get();

	bool AddScene(const std::string& sceneName, std::shared_ptr<Scene> scene);
	std::shared_ptr<Scene> GetScene(const std::string& sceneName) { return mScenes[sceneName]; }
	std::shared_ptr<Scene> GetCurrentScene() { return mCurrentScene; }
	std::shared_ptr<Scene> LoadScene(const std::string& SceneName);
private:
	SceneManager();

	std::shared_ptr<Scene> mCurrentScene;
	std::map<std::string, std::shared_ptr<Scene>> mScenes;

	static SceneManager* m_singleSceneManager;
};

extern SceneManager* g_pSceneManager;