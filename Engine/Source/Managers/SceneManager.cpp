#include "SceneManager.h"
#include "../Scene/Scene.h"
SceneManager* SceneManager::m_singleSceneManager = nullptr;
SceneManager::~SceneManager()
{
}

int SceneManager::Initialize()
{
    return 0;
}

void SceneManager::Tick()
{
}

void SceneManager::Release()
{
    for (const auto& Scene : mScenes)
    {
        Scene.second->Release();
    }
    mScenes.clear();
    delete m_singleSceneManager;
}

SceneManager* SceneManager::Get()
{
    if (m_singleSceneManager == nullptr)
    {
        m_singleSceneManager = new SceneManager;
    }
    return m_singleSceneManager;
}

SceneManager::SceneManager()
{
}

bool SceneManager::AddScene(const std::string& sceneName, std::shared_ptr<Scene> scene)
{
    mScenes[sceneName] = scene;
    return true;
}
std::shared_ptr<Scene> SceneManager::LoadScene(const std::string& SceneName)
{
    mCurrentScene = GetScene(SceneName);
    return mCurrentScene;
}