#include "ButtonDescript.h"

ButtonDescription::ButtonDescription()
{
}

ButtonDescription::ButtonDescription(std::string text, float x, float y, float z, float sizeX, float sizeY, float r, float g, float b)
	:mText(text),
	mPos(x, y, z),
	mSize(sizeX, sizeY),
	mColor(r, g, b)
{
}

void ButtonDescription::Click()
{
}
