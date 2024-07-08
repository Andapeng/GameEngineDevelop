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

private:
	SceneManager();

	std::map<std::string, Scene*> m_scenes;

	static SceneManager* m_singleSceneManager;
};

extern SceneManager* g_pSceneManager;