#include "Paddle.h"
#include "../../Config/GlobalConfiguration.h"
#include "../../Managers/InputManager.h"
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

void Paddle::OnCollide(HitInfo& hitInfo)
{
	RenderableObject::OnCollide(hitInfo);
}

void Paddle::Update(float elapsedTime)
{
	mVelocity = PLAYER_VELOCITY * elapsedTime;
}
