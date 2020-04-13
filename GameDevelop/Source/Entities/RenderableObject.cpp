#include "RenderableObject.h"
#include "../Managers/ResourceManager.h"
#include "../Renderer/SpriteRenderer.h"
#include "../Managers/GraphicsManager.h"
#include "Sprite.h"
extern ResourceManager* g_pResourceManager;
extern GraphicsManager* g_pGraphicsManager;

RenderableObject::RenderableObject()
	:GameObject()
{
	mSprite = std::make_shared<Sprite>();
}

RenderableObject::RenderableObject(std::string texture, int xpos, int ypos, int xsize, int ysize)
	:GameObject()
{
	mSprite = std::make_shared<Sprite>(texture, xpos, ypos, 0, xsize, ysize, 1.0f, 1.0f, 1.0f);
}

RenderableObject::~RenderableObject()
{
}

void RenderableObject::OnRender()
{
	g_pGraphicsManager->GetSpriteRenderer()->RenderSprite(g_pResourceManager->GetTexture(mSprite->GetTexture()), Eigen::Vector2f(mSprite->GetPosX(), mSprite->GetPosY()),
		Eigen::Vector2f(mSprite->GetSizeX(), mSprite->GetSizeY()), 0, Eigen::Vector3f(mSprite->r(), mSprite->g(), mSprite->b()));

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

std::shared_ptr<Sprite> RenderableObject::GetSprite()
{
	return mSprite;
}


