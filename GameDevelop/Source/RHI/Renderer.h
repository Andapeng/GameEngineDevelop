#pragma once
#include "../Math/Math.h"
class Texture2D;

class Renderer
{
public:
	void Initialize();

	void TestRender();
	void RenderSprite(Texture2D tex, Eigen::Vector2f pos, Eigen::Vector2f size, float rotate, Eigen::Vector3f color);
	void Release();

private:
	int InitTextRenderer();
	int InitSpriteRenderer();
	
};