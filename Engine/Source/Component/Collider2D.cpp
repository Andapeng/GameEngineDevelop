#include "Collider2D.h"

bool Collider2D::CheckCollide(const Collider2D& collider, HitInfo& hitInfo)
{
    if (mAABBbox.Contains(collider.mAABBbox))
    {
        return true;
    }
    return false;
}
