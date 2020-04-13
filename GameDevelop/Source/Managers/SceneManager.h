#pragma once
#include <memory>
#include <string>
#include <map>
class GameObject;
class SceneManager
{
public:

private:
	std::map<std::string, std::shared_ptr<GameObject>> mGameObjets;
};