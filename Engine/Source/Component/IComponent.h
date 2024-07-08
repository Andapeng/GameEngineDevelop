#pragma once
#include <memory>
#include <string>
class GameObject;

class IComponent
{
public:
	virtual void Update() = 0;
	virtual std::string GetTypeName() = 0;

	std::shared_ptr<GameObject> GetGameObject() { return mGameObject; }

private:
	std::shared_ptr<GameObject> mGameObject;
};