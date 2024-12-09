#include "Ball.h"
#include "../../Managers/InputManager.h"
#include "../../Managers/SceneManager.h"
#include <math.h>

#include "Brick.h"
#include "Paddle.h"
#include "../../Scene/Scene.h"

Ball::Ball(std::string texture, float xpos, float ypos, float xsize, float ysize, Eigen::Vector3f color)
	: RenderableObject(texture, xpos, ypos, 0.01f, xsize, ysize, color)
{
}

void Ball::OnKeyPressed(const std::string& keyString)
{
    if (mStuck)
    {
        if (keyString == "Left")
        {
            SetPosX(GetPosX() - mPlayerVelocity);
        }
        if (keyString == "Right")
        {
            SetPosX(GetPosX() + mPlayerVelocity);
        }
    }

    if (keyString == "Space")
    {
        mStuck = false;
    }
}
void Ball::Update(float elapsedTime)
{
    Move(elapsedTime, 800);
    mPlayerVelocity = PLAYER_VELOCITY* elapsedTime;
}

Eigen::Vector2f Ball::Move(float dt, float windowWidth)
{
    // if not stuck to player board
    if (!this->mStuck)
    {
        // move the ball
        this->SetPosition2D( GetPosition() + this->mVelocity * dt);
        // check if outside window bounds; if so, reverse velocity and restore at correct position
        if (this->GetPosX() <= 0.0f)
        {
            this->mVelocity[0] = -this->mVelocity[0];
            this->SetPosX(0.0f);
        }
        else if (this->GetPosX() + this->GetSizeX() >= windowWidth)
        {
            this->mVelocity[0] = -this->mVelocity[0];
            this->SetPosX(windowWidth - this->GetSizeX());
        }
        if (this->GetPosY() <= 0.0f)
        {
            this->mVelocity[1] = -this->mVelocity[1];
            this->SetPosY(0.0f);
        }

    }
    return this->GetPosition();
}

void Ball::Reset(Eigen::Vector2f position, Eigen::Vector2f velocity)
{
    this->SetPosition(position.x(),position.y(), 0.01f);
    this->mVelocity = velocity;
    this->mStuck = true;
}

Collision Ball::CheckCollision(std::shared_ptr<RenderableObject> obj)
{
    // get center point circle first 
    Eigen::Vector2f center(GetPosX() + mRadius, GetPosY() + mRadius);
    // calculate AABB info (center, half-extents)
    Eigen::Vector2f aabb_half_extents(obj->GetSizeX() / 2.0f, obj->GetSizeY() / 2.0f);
    Eigen::Vector2f aabb_center(obj->GetPosX() + aabb_half_extents.x(), obj->GetPosY() + aabb_half_extents.y());
    // get difference vector between both centers
    Eigen::Vector2f difference = center - aabb_center;
    float differenceX = std::clamp(difference.x(), -aabb_half_extents.x(), aabb_half_extents.x());
    float differenceY = std::clamp(difference.y(), -aabb_half_extents.y(), aabb_half_extents.y());
    Eigen::Vector2f clamped = { differenceX, differenceY };
    
    // now that we know the clamped values, add this to AABB_center and we get the value of box closest to circle
    Eigen::Vector2f closest = aabb_center + clamped;
    // now retrieve vector between center circle and closest point AABB and check if length < radius
    difference = closest - center;
    ;
    if (difference.norm() < mRadius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, Eigen::Vector2f(0.0f, 0.0f));
}

void Ball::OnCollision(Collision collision, std::shared_ptr<GameObject> obj)
{
    auto brickObj = dynamic_pointer_cast<Brick>(obj);
    if (brickObj)
    {
        // collision resolution
        Direction dir = std::get<1>(collision);
        Eigen::Vector2f diffVector = std::get<2>(collision);
        if (dir == LEFT || dir == RIGHT) // horizontal collision
        {
            mVelocity[0] = -mVelocity[0]; // reverse horizontal velocity
            // relocate
            float penetration = mRadius - std::abs(diffVector.x());
            if (dir == LEFT)
                SetPosX(GetPosX() + penetration); // move ball to right
            else
                SetPosX(GetPosX() - penetration); // move ball to left;
        }
        else // vertical collision
        {
            mVelocity[1] = -mVelocity[1]; // reverse vertical velocity
            // relocate
            float penetration = mRadius - std::abs(diffVector.y());
            if (dir == UP)
                SetPosY(GetPosY() + penetration); // move ball bback up
            else
                SetPosY(GetPosY() - penetration); // move ball back down
        }
    }
	
    auto paddleObj = dynamic_pointer_cast<Paddle>(obj);
    if (!mStuck && paddleObj && std::get<0>(collision))
    {
        // check where it hit the board, and change velocity based on where it hit the board
        float centerBoard = paddleObj->GetPosX() + paddleObj->GetSizeX() / 2.0f;
        float distance = GetPosX() + mRadius - centerBoard;
        float percentage = distance / (paddleObj->GetSizeX() / 2.0f);
        // then move accordingly
        float strength = 2.0f;
        Eigen::Vector2f oldVelocity = mVelocity;
        mVelocity[0] = INITIAL_BALL_VELOCITY.x() * percentage * strength;
        mVelocity.normalize();
        //Ball->Velocity.y = -Ball->Velocity.y;
        mVelocity *= oldVelocity.norm(); // keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // fix sticky paddle
        mVelocity[1] = -1.0f * abs(mVelocity[1]);
    }
}
