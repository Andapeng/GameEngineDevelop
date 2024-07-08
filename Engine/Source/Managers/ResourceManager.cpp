#include "../RHI/Texture.h"
#include "../RHI/Shader.h"
#include "../RHI/Character.h"
#include "ResourceManager.h"
#include <GLAD/glad.h>
ResourceManager* ResourceManager::m_ResourceMgr = nullptr;

ResourceManager* ResourceManager::Get()
{
	if (m_ResourceMgr == nullptr)
	{
		m_ResourceMgr = new ResourceManager;
	}
	return m_ResourceMgr;
}

void ResourceManager::Release()
{
	for (auto texture : m_Textures)
	{
		auto id = texture.second.GetTextureID();
		glDeleteTextures(1, &id);
	}
	for (auto shader : m_Shaders)
	{
		auto program = shader.second.GetID();
		glDeleteShader(program);
	}

	m_Textures.clear();
	m_Shaders.clear();
	m_Characters.clear();
	delete m_ResourceMgr;
}

int ResourceManager::LoadTexture(std::string path, std::string textureName)
{
	Texture2D texture;
	texture.LoadTexture(path, textureName);
	m_Textures[textureName] = texture;
	return 0;
}

Texture2D& ResourceManager::GetTexture(std::string textureName)
{
	return m_Textures[textureName];
}

int ResourceManager::LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath, std::string shaderName)
{
	Shader shader;
	shader.LoadShaderFile(vertexShaderPath.data(), fragmentShaderPath.data());
	m_Shaders[shaderName] = shader;
	return 0;
}

Shader& ResourceManager::GetShader(std::string shaderName)
{
	return m_Shaders[shaderName];
}

int ResourceManager::LoadCharacter(wchar_t unicode, Character ch)
{
	m_Characters[unicode] = ch;
	//mCharacters.insert(std::pair<wchar_t, Character>(unicode, ch));
	return 0;
}

Character& ResourceManager::GetCharacter(wchar_t unicode)
{
	return m_Characters[unicode];
}

ResourceManager::ResourceManager()
{

}