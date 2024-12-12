#include "SpriteRenderer.h"
#include "../RHI/Shader.h"
#include "../RHI/Texture.h"
#include "../RHI/Character.h"	
#include "../Managers/StateManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GraphicsManager.h"
#include "../Managers/FontManager.h"
#include <cstdlib>
#include <iostream>

#include <GLAD/glad.h>
#include "../Log.h"

static float texture_vertices[] =
{
	// Pos      // Tex
	   0.0f, 1.0f, 0.0f, 1.0f,
	   1.0f, 0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 0.0f,

	   0.0f, 1.0f, 0.0f, 1.0f,
	   1.0f, 1.0f, 1.0f, 1.0f,
	   1.0f, 0.0f, 1.0f, 0.0f
};


int SpriteRenderer::Initialize()
{
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_vertices), texture_vertices, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return 0;
}

void SpriteRenderer::RenderSprite(Texture2D tex, Eigen::Vector3f pos, Eigen::Vector2f size, float rotate,
	Eigen::Vector3f color)
{
	Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
	Translate(model, pos);
	Scale(model, Eigen::Vector3f(size(0), size(1), 1.0f));

	ResourceManager::Get()->GetShader("sprite_shader").SetMatrix4f("model", model);
	ResourceManager::Get()->GetShader("sprite_shader").SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	// bind textures on corresponding texture units
	tex.Bind();
	//glBindTexture(GL_TEXTURE_2D, 5);
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}


void SpriteRenderer::AddSprite(std::shared_ptr<Sprite> Sprite)
{
	if (Sprite != nullptr)
	{
		mSpriteRenderQueue[Sprite->GetPosZ()].push_back(Sprite);
	}
}

void SpriteRenderer::OnRender()
{
	// Logger::LogTrace("SpriteRenderer::OnRender begin");

	ResourceManager::Get()->GetShader("sprite_shader").Use();
	for (const auto& SpriteQueue : mSpriteRenderQueue)
	{
		for (const auto& Sprite : SpriteQueue.second)
		{
			 	g_pGraphicsManager->GetSpriteRenderer()->RenderSprite(g_pResourceManager->GetTexture(Sprite->GetTexture()), Eigen::Vector3f(Sprite->GetPosX(), Sprite->GetPosY(), Sprite->GetPosZ()),
 		Eigen::Vector2f(Sprite->GetSizeX(), Sprite->GetSizeY()), 0, Eigen::Vector3f(Sprite->r(), Sprite->g(), Sprite->b()));
		}
	}

	// Logger::LogTrace("SpriteRenderer::OnRender end");
}

void SpriteRenderer::Clear()
{
	mSpriteRenderQueue.clear();
}

int SpriteRenderer::Release()
{
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);

	return 0;
}
