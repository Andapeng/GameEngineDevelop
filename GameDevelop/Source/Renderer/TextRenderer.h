#pragma once
#include <string>
#include "../Math/Math.h"
class TextRenderer
{
public:
	int Initialize();
	void RenderText(std::wstring text, float x, float y, float scale, Eigen::Vector3f color);
	int Release();

private:
	unsigned int textVAO, textVBO;
};