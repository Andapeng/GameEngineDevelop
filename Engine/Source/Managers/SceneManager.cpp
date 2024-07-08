#include "SceneManager.h"
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
