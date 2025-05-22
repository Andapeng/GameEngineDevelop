#pragma once
#include <string>
#include "../Component/Transform.h"
#include "../Component/Collider2D.h"
class HitInfo;
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void OnRender();
	virtual void OnKeyPressed();
	virtual void OnKeyPressed(const std::string& keyString);

	virtual void OnCollide(HitInfo& hitInfo);
	virtual bool IsCollide(std::shared_ptr<GameObject> object);

	virtual void Update(float elapsedTime);

protected:
	std::shared_ptr<Transform> mTransform = nullptr;
	std::shared_ptr<Collider2D> mCollider = nullptr;

private:
	int m_objectID = 0;
	int m_instanceID = 0;
	
};