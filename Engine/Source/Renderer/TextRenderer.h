#pragma once
#include <string>
#include "../Math/Math.h"
#include "../Entities/Text.h"
class TextRenderer
{
public:
	int Initialize();
	int Release();

	void AddText(std::shared_ptr<Text> Text);
	void Clear();

	void RenderText(std::wstring text, float x, float y, float scale, Eigen::Vector3f color);
	void OnRender();
private:
	unsigned int textVAO = 0;
	unsigned int textVBO = 0;

	std::vector<std::shared_ptr<Text>> mTexts;
};