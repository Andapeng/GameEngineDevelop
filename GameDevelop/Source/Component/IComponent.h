#pragma once
#include <memory>

class GameObject;

class IComponent
{
public:
	virtual int GetType() = 0;
	virtual bool IsType() = 0;
	virtual void Update() = 0;

	std::shared_ptr<GameObject> GetGameObject() { return mGameObject; }

private:
	std::shared_ptr<GameObject> mGameObject;
};