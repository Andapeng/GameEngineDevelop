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
    mGameObjectsMap.clear();
}

bool Scene::AddGameObject(const std::string& objectName, std::shared_ptr<GameObject> gameObject)
{
    mGameObjectsMap[objectName] = gameObject;
    return true;
}

std::shared_ptr<GameObject> Scene::GetGameObject(const std::string& objectName)
{
    if (mGameObjectsMap.contains(objectName))
    {
        return mGameObjectsMap[objectName];
    }
    return nullptr;
}
