#pragma once
#include <string>
#include "../math/Math.h"
class Text
{
public:
	Text();
	Text(std::wstring text, float x, float y, float z, float sizeX, float sizeY, float r, float g, float b);

	void SetPosX(float x) { mPos[0] = x; }
	void SetPosY(float y) { mPos[1] = y; }

	void SetText(const std::wstring& text) { mText = text; }
	std::wstring GetText() { return mText; }
	float GetPosX() { return mPos[0]; }
	float GetPosY() { return mPos[1]; }
	float GetSizeX() { return mSize[0]; }
	float GetSizeY() { return mSize[1]; }
	float r() { return mColor[0]; }
	float g() { return mColor[1]; }
	float b() { return mColor[2]; }
private:

	std::wstring mText;
	Eigen::Vector3f mPos;
	Eigen::Vector2f mSize;
	Eigen::Vector3f mColor;
};