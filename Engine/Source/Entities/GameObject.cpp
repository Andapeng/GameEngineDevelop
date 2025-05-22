
#include "GameObject.h"
#include "../Renderer/SpriteRenderer.h"

#include "../Physics/HitInfo.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
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

void GameObject::Update(float elapsedTime) {}