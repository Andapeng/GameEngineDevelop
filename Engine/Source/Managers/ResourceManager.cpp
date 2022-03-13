#include "../RHI/Texture.h"
#include "../RHI/Shader.h"
#include "../RHI/Character.h"
#include "ResourceManager.h"
#include <GLAD/glad.h>
ResourceManager* ResourceManager::mResourceMgr = nullptr;

ResourceManager* ResourceManager::Get()
{
	if (mResourceMgr == nullptr)
	{
		mResourceMgr = new ResourceManager;
	}
	return mResourceMgr;
}

void ResourceManager::Release()
{
	for (auto texture : mTextures)
	{
		auto id = texture.second.GetTextureID();
		glDeleteTextures(1, &id);
	}
	for (auto shader : mShaders)
	{
		auto program = shader.second.GetID();
		glDeleteShader(program);
	}

	mTextures.clear();
	mShaders.clear();
	mCharacters.clear();
	delete mResourceMgr;
}

int ResourceManager::LoadTexture(std::string path, std::string textureName)
{
	Texture2D texture;
	texture.LoadTexture(path, textureName);
	mTextures[textureName] = texture;
	return 0;
}

Texture2D& ResourceManager::GetTexture(std::string textureName)
{
	return mTextures[textureName];
}

int ResourceManager::LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string shaderName)
{
	Shader shader;
	shader.LoadShaderFile(vertexShaderPath.data(), fragmentShaderPath.data());
	mShaders[shaderName] = shader;
	return 0;
}

Shader& ResourceManager::GetShader(std::string shaderName)
{
	return mShaders[shaderName];
}

int ResourceManager::LoadCharacter(wchar_t unicode, Character ch)
{
	mCharacters[unicode] = ch;
	//mCharacters.insert(std::pair<wchar_t, Character>(unicode, ch));
	return 0;
}

Character& ResourceManager::GetCharacter(wchar_t unicode)
{
	return mCharacters[unicode];
}

ResourceManager::ResourceManager()
{

}