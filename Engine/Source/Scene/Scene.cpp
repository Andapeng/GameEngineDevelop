#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::AddGameObject(std::string objectName, GameObject* gameObject)
{
    m_GameObjectsMap[objectName] = gameObject;
    return true;
}
