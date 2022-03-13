#pragma once
#include "GameObject.h"
#include <memory>
class Sprite;
class RenderableObject : public GameObject
{
public:
	RenderableObject();
	RenderableObject(std::string texture, int xpos, int ypos, int xsize, int ysize);
	~RenderableObject();

	void OnRender() override;
	
	void SetPosition(float x, float y, float z);
	float GetPosX();
	float GetPosY();

	std::shared_ptr<Sprite> GetSprite();
	
private:


	std::shared_ptr<Sprite> mSprite;
};