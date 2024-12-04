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

RenderableObject::RenderableObject(std::string texture, int xpos, int ypos, int xsize, int ysize, Eigen::Vector3f color)
	:GameObject()
{
	mSprite = std::make_shared<Sprite>(texture, xpos, ypos, 0, xsize, ysize, color.x(), color.y(), color.z());
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

std::shared_ptr<Sprite> RenderableObject::GetSprite()
{
	return mSprite;
}


