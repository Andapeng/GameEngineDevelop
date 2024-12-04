#pragma once
#include <string>
#include "../math/Math.h"

class ButtonDescription
{
public:
	ButtonDescription();
	ButtonDescription(std::string text, float x, float y, float z, float sizeX, float sizeY, float r, float g, float b);

	void SetPosX(float x) { mPos[0] = x; }
	void SetPosY(float y) { mPos[1] = y; }

	void SetText(const std::string& text) { mText = text; }
	std::string GetText() { return mText; }
	float GetPosX() { return mPos[0]; }
	float GetPosY() { return mPos[1]; }
	float GetSizeX() { return mSize[0]; }
	float GetSizeY() { return mSize[1]; }
	float r() { return mColor[0]; }
	float g() { return mColor[1]; }
	float b() { return mColor[2]; }
	void Click();
private:
	std::string mText;
	Eigen::Vector3f mPos;
	Eigen::Vector2f mSize;
	Eigen::Vector3f mColor;
	bool bClicked = false;
};