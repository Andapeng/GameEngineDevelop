#pragma once
#include "IManager.h"
#include <string>
#include <map>
class Texture2D;
class Shader;
class Character;

class ResourceManager : public IManager
{
public:
	static ResourceManager* Get();

	virtual int Initialize() override { return 1; }
	virtual void Tick() override {}
	virtual void Release() override;

	int LoadTexture(std::string path, std::string textureName);
	Texture2D& GetTexture(std::string);

	int LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath,
		std::string shaderName);
	Shader& GetShader(std::string);

	int LoadCharacter(wchar_t u8char, Character ch);
	Character& GetCharacter(wchar_t u8char);

private:
	ResourceManager();
	static ResourceManager* mResourceMgr;

	std::map<std::string, Texture2D> mTextures;
	std::map<std::string, Shader> mShaders;
	std::map<wchar_t, Character> mCharacters;

};

extern ResourceManager* g_pResourceManager;