#pragma once
#include "../../Entities/RenderableObject.h"
class PowerUp : public RenderableObject
{
public:

    // constructor
    PowerUp(std::string type, Eigen::Vector3f color, float duration,
        Eigen::Vector2f position, std::string texture);

    virtual void Update(float elapsedTime) override;

    void SetActivated(bool bActivated) { mActivated = bActivated; }
    void SetDestroyed(bool bDestroyed) { mDestroyed = bDestroyed; }
    bool IsDestroyed() { return mDestroyed; }

    std::string GetType() { return mType; }
    bool IsActivated() { return mActivated; }
    Eigen::Vector2f GetVelocity() { return VELOCITY; }

private:
    const Eigen::Vector2f VELOCITY = { 0.0f, 150.0f };

    // powerup state
    std::string mType;
    float       mDuration = 0.0f;
    bool        mActivated = false;
    bool        mDestroyed = false;
};