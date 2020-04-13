#pragma once
#include "../Math/Math.h"
#include "../RHI/Texture.h"

class SpriteRenderer
{
public:
	int Initialize();
	void RenderSprite(Texture2D tex, Eigen::Vector2f pos, Eigen::Vector2f size, float rotate, Eigen::Vector3f color);
	void RenderSprite(unsigned int tex, Eigen::Vector2f pos, Eigen::Vector2f size, float rotate, Eigen::Vector3f color);
	int Release();


private:
	unsigned int quadVAO, quadVBO;

	// µ¥Àý£¿
};