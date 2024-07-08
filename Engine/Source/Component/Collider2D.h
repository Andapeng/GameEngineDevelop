#pragma once
#include <box2D/box2d.h>
#include "IComponent.h"
#include "../Physics/HitInfo.h"

class Collider2D : public IComponent
{
public:
	virtual void Update() {}
	std::string GetTypeName() override { return "Collider2D"; };
	b2AABB GetAABBBox() { return mAABBbox; }
	bool CheckCollide(const Collider2D& collider, HitInfo& hitInfo);
private:
	b2AABB mAABBbox;
};
