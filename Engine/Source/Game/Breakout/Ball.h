#pragma once
#include <string>
#include "../../Entities/RenderableObject.h"
#include "../../Physics/Physics2D.h"
class Ball : public RenderableObject
{
public:
    Ball(std::string texture, float xpos = 0.0f, float ypos = 0.0f, float xsize = 50.0f, float ysize = 50.0f, Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });

    virtual void OnKeyPressed(const std::string& keyString) override;
    virtual void Update(float elapsedTime) override;

    Eigen::Vector2f Move(float dt, float windowWidth);
    void      Reset(Eigen::Vector2f position, Eigen::Vector2f velocity);

    Collision CheckCollision(std::shared_ptr<RenderableObject> obj);
    void OnCollision(Collision collision, std::shared_ptr<GameObject> obj);
private:
    // Initial velocity of the Ball
    const Eigen::Vector2f INITIAL_BALL_VELOCITY = { 100.0f, -350.0f };
    // Radius of the ball object
    const float BALL_RADIUS = 12.5f;

    // ball state	
    float     mRadius = BALL_RADIUS;
    bool      mStuck = true;
    Eigen::Vector2f mVelocity = INITIAL_BALL_VELOCITY;

    float mWindowWidth = 0.0f;
    const float PLAYER_VELOCITY = 5000.0f;
    float mPlayerVelocity = 0.0f;
};
