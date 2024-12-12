#pragma once
#include "GameObject.h"
#include <memory>
class Sprite;
class RenderableObject : public GameObject
{
public:
	RenderableObject();
	RenderableObject(std::string texture, float xpos, float ypos, float xsize, float ysize, Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });
	RenderableObject(std::string texture, float xPos, float yPos, float zPos, float xSize, float ySize, Eigen::Vector3f color = { 1.0f, 1.0f, 1.0f });
	~RenderableObject() override;

	virtual void OnRender() override;
	
	void SetPosition(float x, float y, float z);
	void SetPosition(Eigen::Vector3f pos);
	void SetPosition2D(Eigen::Vector2f pos);
	Eigen::Vector2f GetPosition() { return { mSprite->GetPosX(), mSprite->GetPosY() }; }
	void SetPosX(float x) { mSprite->SetPosX(x); }
	void SetPosY(float y) { mSprite->SetPosY(y); }
	void SetSize(Eigen::Vector2f size);
	float GetPosX();
	float GetPosY();
	float GetSizeX();
	float GetSizeY();
	std::shared_ptr<Sprite> GetSprite();
	
private:
	std::shared_ptr<Sprite> mSprite = nullptr;
};