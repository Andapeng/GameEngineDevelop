#include "RenderableObject.h"
#include "../Managers/ResourceManager.h"
#include "../Renderer/SpriteRenderer.h"
#include "../Managers/GraphicsManager.h"
#include "Sprite.h"

RenderableObject::RenderableObject()
	:GameObject()
{
	mSprite = std::make_shared<Sprite>();
}

RenderableObject::RenderableObject(std::string texture, float xpos, float ypos, float xsize, float ysize, Eigen::Vector3f color)
	:GameObject()
{
	mSprite = std::make_shared<Sprite>(texture, xpos, ypos, 0, xsize, ysize, color.x(), color.y(), color.z());
}

RenderableObject::RenderableObject(std::string texture, float xPos, float yPos, float zPos, float xSize, float ySize,
	Eigen::Vector3f color)
{
	mSprite = std::make_shared<Sprite>(texture, xPos, yPos, zPos, xSize, ySize, color.x(), color.y(), color.z());
}

RenderableObject::~RenderableObject()
{
}

void RenderableObject::OnRender()
{
	g_pGraphicsManager->GetSpriteRenderer()->AddSprite(mSprite);
}

void RenderableObject::SetPosition(float x, float y, float z)
{
	mSprite->SetPosX(x);
	mSprite->SetPosY(y);
}

void RenderableObject::SetPosition(Eigen::Vector3f pos)
{
	mSprite->SetPosX(pos.x());
	mSprite->SetPosY(pos.y());
}

void RenderableObject::SetPosition2D(Eigen::Vector2f pos)
{
	mSprite->SetPosX(pos.x());
	mSprite->SetPosY(pos.y());
}

void RenderableObject::SetSize(Eigen::Vector2f size)
{
	mSprite->SetSizeX(size[0]);
	mSprite->SetSizeY(size[1]);
}

float RenderableObject::GetPosX()
{
	return mSprite->GetPosX();
}

float RenderableObject::GetPosY()
{
	return mSprite->GetPosY();
}

float RenderableObject::GetSizeX()
{
	return mSprite->GetSizeX();
}

float RenderableObject::GetSizeY()
{
	return mSprite->GetSizeY();
}

std::shared_ptr<Sprite> RenderableObject::GetSprite()
{
	return mSprite;
}


