#pragma once
#include <string>
#include "../../Entities/RenderableObject.h"

class Paddle : public RenderableObject
{
public:
	Paddle(std::string texture, float xpos = 0.0f, float ypos = 0.0f, float xsize = 50.0f, float ysize = 50.0f, Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });
	virtual void OnKeyPressed(const std::string& keyString);

	virtual void OnCollide(HitInfo& hitInfo);

	virtual void Update(float elapsedTime);
private:
	float mVelocity = 0.0f;
};
