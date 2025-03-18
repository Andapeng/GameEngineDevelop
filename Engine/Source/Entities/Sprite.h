#pragma once
#include <string>
#include "../math/Math.h"
class Sprite
{
public:
	Sprite();
	Sprite(std::string texture, float x, float y, float z, float sizeX, float sizeY, float r, float g, float b);

	void SetPosX(float x) { mPos[0] = x; }
	void SetPosY(float y) { mPos[1] = y; }
	void SetSizeX(float x) { mSize[0] = x; }
	void SetSizeY(float y) { mSize[1] = y; }
	void SetColor(Eigen::Vector3f color) { mColor = color; }

	std::string GetTexture() { return mTexture; }
	float GetPosX() { return mPos[0]; }
	float GetPosY() { return mPos[1]; }
	float GetPosZ() { return mPos[2]; }
	float GetSizeX() { return mSize[0]; }
	float GetSizeY() { return mSize[1]; }
	float r() { return mColor[0]; }
	float g() { return mColor[1]; }
	float b() { return mColor[2]; }
private:
	
	std::string mTexture;
	Eigen::Vector3f mPos;
	Eigen::Vector2f mSize;
	Eigen::Vector3f mColor;
};