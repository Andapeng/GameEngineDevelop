#pragma once
#include <string>
#include "../Component/Transform.h"
#include "Sprite.h"
class HitInfo;
class GameObject
{
public:
	GameObject();
	GameObject(GameObject& obj);
	~GameObject();
	virtual void OnRender();
	virtual void OnKeyPressed();

	virtual void OnCollide(HitInfo& hitInfo);
	virtual bool IsCollide(GameObject* object);

	virtual void Update(float elasedTime);

protected:
	Transform* mTransform;
	Sprite* mSprite;

private:
	int mObjectID;
	int mInstanceID;
	
};