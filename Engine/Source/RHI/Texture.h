#pragma once
#include <string>
class Texture2D
{
public:
	Texture2D();
	~Texture2D();
	int LoadTexture(std::string path, std::string textureName);
	unsigned int GetTextureID() { return mTextureID; }
	void Bind();
private:
	unsigned int mTextureID;
};