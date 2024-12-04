#pragma once
#include "GameObject.h"
#include <memory>
class Sprite;
class RenderableObject : public GameObject
{
public:
	RenderableObject();
	RenderableObject(std::string texture, int xpos, int ypos, int xsize, int ysize, Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });
	~RenderableObject() override;

	void OnRender() override;
	
	void SetPosition(float x, float y, float z);
	float GetPosX();
	float GetPosY();
	float GetSizeX();
	std::shared_ptr<Sprite> GetSprite();
	
private:


	std::shared_ptr<Sprite> mSprite;
};