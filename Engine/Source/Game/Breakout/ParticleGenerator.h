#pragma once
#include <map>
#include <memory>

#include "../../Entities/RenderableObject.h"
#include "../../Math/Math.h"
class GameObject;
class Particle;

class ParticleGenerator : public RenderableObject
{
public:
	ParticleGenerator(std::string texture, unsigned int amount, std::shared_ptr<GameObject> attachObj, unsigned int newParticles, Eigen::Vector2f offset = {0.0f, 0.0f});

	virtual void Update(float elapsedTime) override;
	virtual void OnRender() override;

private:
	// returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
	std::shared_ptr<Particle> firstUnusedParticle();

	// respawns particle
	void respawnParticle(std::shared_ptr<Particle> particle, std::shared_ptr<GameObject> attachObject, Eigen::Vector2f offset);

	Eigen::Vector2f mVelocity;
	std::shared_ptr<GameObject> mAttachObj;

	unsigned int mAmount = 0;
	unsigned int mNewParticles = 0;
	Eigen::Vector2f mOffset;
	size_t LastUsedParticleIndex = 0;
	std::vector <std::shared_ptr<Particle>> mParticles;
	std::map<std::shared_ptr<Particle>, float> mParticlesLifecycle;
};
