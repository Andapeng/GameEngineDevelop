#pragma once
#include <map>

#include "../Math/Math.h"
#include "../RHI/Texture.h"
#include "../Entities/RenderableObject.h"
class SpriteRenderer
{
public:
	int Initialize();
	int Release();

	void AddSprite(std::shared_ptr<Sprite> sprite);
	void Clear();

	void RenderSprite(Texture2D tex, Eigen::Vector3f pos, Eigen::Vector2f size, float rotate, Eigen::Vector3f color);
	void OnRender();
private:

	unsigned int quadVAO = 0;
	unsigned int quadVBO = 0;

	std::map<float, std::vector<std::shared_ptr<Sprite>>> mSpriteRenderQueue;
	// µ¥Àý£¿
};