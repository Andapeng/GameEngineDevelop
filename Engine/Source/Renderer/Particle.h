#pragma once
#include <string>

#include "../math/Math.h"

class Particle
{
public:
	Particle(std::string mTexture, Eigen::Vector3f pos = { 0.0f, 0.0f, 0.0f }, Eigen::Vector2f size = { 0.0f, 0.0f }, Eigen::Vector4f color = { 1.0f, 1.1f, 1.0f, 1.0f });

	void SetPosX(float x) { mPos[0] = x; }
	void SetPosY(float y) { mPos[1] = y; }
	void SetSizeX(float x) { mSize[0] = x; }
	void SetSizeY(float y) { mSize[1] = y; }
	void SetColor(Eigen::Vector4f color) { mColor = color; }
	void SetColorAlpha(float alpha) { mColor[3] = alpha; }

	std::string GetTexture() { return mTexture; }
	float GetPosX() { return mPos[0]; }
	float GetPosY() { return mPos[1]; }
	float GetPosZ() { return mPos[2]; }
	float GetSizeX() { return mSize[0]; }
	float GetSizeY() { return mSize[1]; }
	Eigen::Vector4f GetColor() { return mColor; }
	float r() { return mColor[0]; }
	float g() { return mColor[1]; }
	float b() { return mColor[2]; }
	
private:
    std::string mTexture;
    Eigen::Vector3f mPos;
    Eigen::Vector2f mSize;
    Eigen::Vector4f mColor;
};