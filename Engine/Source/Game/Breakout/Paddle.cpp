#include "Paddle.h"
#include "../../Config/GlobalConfiguration.h"
#include "../../Managers/InputManager.h"
Paddle::Paddle(std::string texture, int xpos, int ypos, int xsize, int ysize, Eigen::Vector3f color)
	: RenderableObject(texture, xpos, ypos, xsize, ysize, color)
{

}

void Paddle::OnRender()
{
	RenderableObject::OnRender();
}

void Paddle::OnKeyPressed()
{
	if (g_pInputManager->IsKeyPressed("Left"))
	{
		if (GetPosX() >= 0.0f)
		{
			SetPosition(GetPosX() - mVelocity, GetPosY(), 0);
		}
	}
	else if (g_pInputManager->IsKeyPressed("Right"))
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

bool Paddle::IsCollide(GameObject* object)
{
	return RenderableObject::IsCollide(object);
}

void Paddle::Update(float elaspedTime)
{
	mVelocity = PLAYER_VELOCITY * elaspedTime;
}
