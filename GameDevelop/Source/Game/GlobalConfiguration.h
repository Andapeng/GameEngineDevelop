#pragma once
const int DEFAULT_WIDTH = 800;
const int DEFAULT_HEIGHT = 600;

class Configuration
{
public:

	static Configuration* Get();

	int Load(const char* pathName);
	int Save(const char* pathName);

	int GetWidth()const { return mWidth; }
	int GetHeight()const { return mHeight; }
private:
	int mWidth;
	int mHeight;

	Configuration();

	static Configuration* mSingleConfig;
};