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
    m_GameObjectsMap.clear();
}

bool Scene::AddGameObject(const std::string& objectName, std::shared_ptr<GameObject> gameObject)
{
    m_GameObjectsMap[objectName] = gameObject;
    return true;
}
