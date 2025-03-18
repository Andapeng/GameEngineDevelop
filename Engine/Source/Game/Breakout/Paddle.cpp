#include "Paddle.h"
#include "../../Config/GlobalConfiguration.h"
#include "../../Managers/InputManager.h"
#include "GameConfig.h"
Paddle::Paddle(std::string texture, float xpos, float ypos, float xsize, float ysize, Eigen::Vector3f color)
	: RenderableObject(texture, xpos, ypos, xsize, ysize, color)
{
	mVelocity = PLAYER_VELOCITY;
}

void Paddle::OnKeyPressed(const std::string& keyString)
{
	if (keyString == "Left")
	{
		if (GetPosX() >= 0.0f)
		{
			SetPosition(GetPosX() - mVelocity, GetPosY(), 0);
		}
	}
	else if (keyString == "Right")
	{
		if (GetPosX() <= Configuration::Get()->GetWidth() - GetSizeX()) {
			SetPosition(GetPosX() + mVelocity, GetPosY(), 0);
		}
	}
}

bool Paddle::CheckCollision(std::shared_ptr<RenderableObject> obj)
{
	// collision x-axis?
	bool collisionX = GetPosX() + GetSizeX() >= obj->GetPosX() &&
		obj->GetPosX() + obj->GetSizeX() >= GetPosX();
	// collision y-axis?
	bool collisionY = GetPosY() + GetSizeY() >= obj->GetPosY() &&
		obj->GetPosY() + obj->GetSizeY() >= GetPosY();
	// collision only if on both axes
	return collisionX && collisionY;
}

void Paddle::OnCollision(Collision collision, std::shared_ptr<GameObject> obj)
{

}

void Paddle::Update(float elapsedTime)
{
	mVelocity = PLAYER_VELOCITY * elapsedTime;
}
