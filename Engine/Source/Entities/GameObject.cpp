
#include "GameObject.h"
#include "../Renderer/SpriteRenderer.h"

#include "../Physics/HitInfo.h"

GameObject::GameObject()
	:m_objectID(0),
	m_instanceID(0)
{
	m_transform = nullptr;
	m_sprite = nullptr;
}

GameObject::GameObject(GameObject& obj)
{
	this->m_objectID = obj.m_objectID;
}

GameObject::~GameObject()
{
	delete m_transform;
	delete m_sprite;
}

void GameObject::OnRender()
{
}

void GameObject::OnKeyPressed()
{
}

void GameObject::OnKeyPressed(const std::string& keyString)
{
}

void GameObject::OnCollide(HitInfo& hitInfo)
{
}

bool GameObject::IsCollide(std::shared_ptr<GameObject> object)
{
	// get physics component
	// call component check collide function
	
	return false;
}

void GameObject::Update(float elasedTime)
{
}

std::vector<std::shared_ptr<IComponent>> GameObject::GetComponents(std::string TypeName)
{
	return std::vector<std::shared_ptr<IComponent>>();
}

std::shared_ptr<IComponent> GameObject::GetComponent(std::string componentName)
{
	return nullptr;
}
