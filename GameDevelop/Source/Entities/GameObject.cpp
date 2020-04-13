
#include "GameObject.h"

#include "../Managers/ResourceManager.h"
#include "../Renderer/SpriteRenderer.h"

#include "../Physics/HitInfo.h"

#include <Eigen/Core>
extern ResourceManager* g_pResourceManager;

GameObject::GameObject()
	:mObjectID(0),
	mInstanceID(0)
{
	mTransform = nullptr;
	mSprite = nullptr;
}

GameObject::GameObject(GameObject& obj)
{
	this->mObjectID = obj.mObjectID;
}

GameObject::~GameObject()
{
	delete mTransform;
	delete mSprite;
}

void GameObject::OnRender()
{
}

void GameObject::OnKeyPressed()
{
}

void GameObject::OnCollide(HitInfo& hitInfo)
{
}

void GameObject::Update(float elasedTime)
{
}
