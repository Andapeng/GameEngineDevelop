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
	int GetDepthBits()const { return mDepthBits; }
	int GetStencilBits()const { return mStencilBits; }
	int GetMajorVersion()const { return mMajorVersion; }
	int GetMinorVersion()const { return mMinorVersion; }
private:
	int mWidth;
	int mHeight;
	int mDepthBits;
	int mStencilBits;
	int mMajorVersion;
	int mMinorVersion;

	Configuration();

	static Configuration* mSingleConfig;
};