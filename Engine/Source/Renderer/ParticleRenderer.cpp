#include "ParticleRenderer.h"

#include <format>
#include <GLAD/glad.h>

#include "../RHI/Shader.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GraphicsManager.h"

#include "Particle.h"
#include "../Log.h"

static float ParticleVertices[] =
{
	// Pos      // Tex
	   0.0f, 1.0f, 0.0f, 1.0f,
	   1.0f, 0.0f, 1.0f, 0.0f,
	   0.0f, 0.0f, 0.0f, 0.0f,

	   0.0f, 1.0f, 0.0f, 1.0f,
	   1.0f, 1.0f, 1.0f, 1.0f,
	   1.0f, 0.0f, 1.0f, 0.0f
};

int ParticleRenderer::Initialize()
{
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ParticleVertices), ParticleVertices, GL_STATIC_DRAW);

	glBindVertexArray(quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return 0;
}

int ParticleRenderer::Release()
{
	Clear();
	return 0;
}

void ParticleRenderer::AddParticle(std::shared_ptr<Particle> particle)
{
	if (particle != nullptr)
	{
		mParticleRenderQueue[particle->GetPosZ()].push_back(particle);
	}
}

void ParticleRenderer::Clear()
{
	mParticleRenderQueue.clear();
}

void ParticleRenderer::RenderParticle(Texture2D tex, Eigen::Vector3f pos, Eigen::Vector4f color)
{
	// Logger::LogInfo(std::format("pos = ({}, {})", pos(0), pos(1)));
	g_pResourceManager->GetShader("particle_shader").Use();
	g_pResourceManager->GetShader("particle_shader").SetVector2f("offset", {pos(0), pos(1)});
	g_pResourceManager->GetShader("particle_shader").SetVector4f("color", color);
	glActiveTexture(GL_TEXTURE0);
	// bind textures on corresponding texture units
	tex.Bind();
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void ParticleRenderer::OnRender()
{
	// Logger::LogTrace("ParticleRenderer::OnRender begin");
	// use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (const auto& ParticleQueue : mParticleRenderQueue)
	{
		for (const auto& Particle : ParticleQueue.second)
		{
			RenderParticle(g_pResourceManager->GetTexture(Particle->GetTexture()), Eigen::Vector3f(Particle->GetPosX(), Particle->GetPosY(), Particle->GetPosZ())
				, Particle->GetColor());
		}
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Logger::LogTrace("ParticleRenderer::OnRender end");
}
