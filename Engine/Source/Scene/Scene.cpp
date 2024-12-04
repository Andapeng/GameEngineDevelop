#include "Scene.h"
#include "../Entities/GameObject.h"
Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Release()
{
    for (auto gameObject : m_GameObjectsMap)
    {
        delete gameObject.second;
    }
    m_GameObjectsMap.clear();
}

bool Scene::AddGameObject(const std::string& objectName, GameObject* gameObject)
{
    m_GameObjectsMap[objectName] = gameObject;
    return true;
}
