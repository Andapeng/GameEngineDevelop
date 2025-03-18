#pragma once
#include <string>
class Texture2D
{
public:
	Texture2D();
	~Texture2D();
	int Generate(unsigned int width, unsigned int height, const char* data);
	int LoadTexture(std::string path, std::string textureName);
	unsigned int GetTextureID() { return mTextureID; }
	void Bind();
private:
	unsigned int mTextureID;
};