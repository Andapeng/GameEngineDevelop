#pragma once
#include <box2D/box2d.h>
#include "../Physics/HitInfo.h"

class GameObject;

class Collider2D
{
    enum class ColliderShape
    {
        BOX,
        CIRCLE
    };
  public:
    Collider2D(float width, float height, std::shared_ptr<GameObject> obj);
    Collider2D(float radius, std::shared_ptr<GameObject> obj);
    bool CheckCollide(const Collider2D& collider, HitInfo& hitInfo);
    std::shared_ptr<GameObject> GetOwner() { return mGameObj; }
    ColliderShape GetColliderShape() const { return mShape; }

  private:
    b2AABB mAABBBox;
    b2CircleShape mCircle;
    bool bIsVisible = false;
    ColliderShape mShape = ColliderShape::BOX;
    std::shared_ptr<GameObject> mGameObj = nullptr;
};



