#pragma once
#include "IManager.h"
#include <string>
#include <map>
class Texture2D;
class Shader;
class Character;
namespace sf
{
	class SoundBuffer;
}
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
	static ResourceManager* m_ResourceMgr;

	std::map<std::string, Texture2D> m_Textures;
	std::map<std::string, Shader> m_Shaders;
	std::map<wchar_t, Character> m_Characters;
};

extern ResourceManager* g_pResourceManager;