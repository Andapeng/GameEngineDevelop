#pragma once
#include <map>
#include <memory>
#include <vector>
#include "../math/Math.h"
#include "../RHI/Texture.h"

class Particle;

class ParticleRenderer
{
public:
	int Initialize();
	int Release();

	void AddParticle(std::shared_ptr<Particle> particle);
	void Clear();

	void RenderParticle(Texture2D tex, Eigen::Vector3f pos, Eigen::Vector4f color);
	void OnRender();
private:
	unsigned int quadVAO = 0;
	unsigned int quadVBO = 0;

	std::map<float, std::vector<std::shared_ptr<Particle>>> mParticleRenderQueue;

};
