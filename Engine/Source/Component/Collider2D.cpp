#include "Collider2D.h"

Collider2D::Collider2D(float width,
                              float height,
                              std::shared_ptr<GameObject> obj)
    : mShape(ColliderShape::BOX)
{
}
Collider2D::Collider2D(float radius, std::shared_ptr<GameObject> obj) 
    : mShape(ColliderShape::CIRCLE)
{
}

bool Collider2D::CheckCollide(const Collider2D& collider, HitInfo& hitInfo)
{
    // Check if the AABBs of the two colliders overlap
    if (mAABBbox.Contains(collider.mAABBbox))
    {
        return true;
    }
    return false;
}
