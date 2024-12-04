#pragma once
#include <string>
#include "../../Entities/RenderableObject.h"

class Paddle : public RenderableObject
{
public:
	Paddle(std::string texture, int xpos = 0, int ypos = 0, int xsize = 50, int ysize = 50, Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });
	virtual void OnRender();
	virtual void OnKeyPressed();

	virtual void OnCollide(HitInfo& hitInfo);
	virtual bool IsCollide(GameObject* object);

	virtual void Update(float elaspedTime);
private:
	float mVelocity = 0.0f;
	const float PLAYER_VELOCITY = 5000.0f;
};
