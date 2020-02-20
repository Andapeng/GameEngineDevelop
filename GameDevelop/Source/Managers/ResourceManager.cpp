#include "../RHI/Texture.h"
#include "../RHI/Shader.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::mResourceMgr = nullptr;

ResourceManager* ResourceManager::Get()
{
	if (mResourceMgr == nullptr)
	{
		mResourceMgr = new ResourceManager;
	}
	return mResourceMgr;
}

int ResourceManager::LoadTexture(std::string path, std::string textureName)
{
	Texture2D texture;
	texture.LoadTexture(path, textureName);
	mTextures[textureName] = texture;
	return 0;
}

Texture2D ResourceManager::GetTexture(std::string textureName)
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

Shader ResourceManager::GetShader(std::string shaderName)
{
	return mShaders[shaderName];
}

ResourceManager::ResourceManager()
{

}