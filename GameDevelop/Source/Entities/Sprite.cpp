#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string texture, float x, float y, float z, float sizeX, float sizeY, float r, float g, float b)
	:mTexture(texture),
	mPos(x,y,z),
	mSize(sizeX, sizeY),
	mColor(r,g,b)
{
}
