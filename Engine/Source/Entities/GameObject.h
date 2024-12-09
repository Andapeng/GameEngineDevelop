#pragma once
#include <string>
#include "../Component/Transform.h"
#include "../Component/Collider2D.h"
#include "Sprite.h"
#include <vector>
class HitInfo;
class GameObject
{
public:
	GameObject();
	GameObject(GameObject& obj);
	virtual ~GameObject();
	virtual void OnRender();
	virtual void OnKeyPressed();
	virtual void OnKeyPressed(const std::string& keyString);

	virtual void OnCollide(HitInfo& hitInfo);
	virtual bool IsCollide(std::shared_ptr<GameObject> object);

	virtual void Update(float elapsedTime);

protected:
	std::vector<std::shared_ptr<IComponent>> GetComponents(std::string TypeName);
	std::shared_ptr<IComponent> GetComponent(std::string componentName);

	Transform* m_transform;
	Sprite* m_sprite;
	std::shared_ptr<Collider2D> m_collider;
	std::vector<std::shared_ptr<IComponent>> m_components;

private:
	int m_objectID;
	int m_instanceID;
	
};