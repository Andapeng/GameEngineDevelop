#include "PowerUp.h"
const Eigen::Vector2f SIZE = { 60.0f, 20.0f };

PowerUp::PowerUp(std::string type, Eigen::Vector3f color, float duration, Eigen::Vector2f position, std::string texture)
    : RenderableObject(texture, position.x(), position.y(), SIZE.x(), SIZE.y(), color),
    mType(type), mDuration(duration), mActivated()
{ }

void PowerUp::Update(float elapsedTime)
{
    SetPosition2D(GetPosition2D() + GetVelocity() * elapsedTime);
    if (IsActivated())
    {
        mDuration -= elapsedTime;
        if (mDuration <= 0)
        {
            SetActivated(false);
        }
    }
}
