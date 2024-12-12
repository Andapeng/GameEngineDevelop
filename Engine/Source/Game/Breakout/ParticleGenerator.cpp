#include "ParticleGenerator.h"

#include <format>

#include "Ball.h"
#include "../../Entities/RenderableObject.h"
#include "../../Renderer/Particle.h"

#include "../../Managers/GraphicsManager.h"
#include "../../Renderer/ParticleRenderer.h"

#include "../../Log.h"

#include "GameConfig.h"
static float sTime = 0;

ParticleGenerator::ParticleGenerator(std::string texture, unsigned amount, std::shared_ptr<GameObject> attachObj, unsigned int newParticles, Eigen::Vector2f offset)
	: mAmount(amount)
	, mAttachObj(attachObj)
	, mNewParticles(newParticles)
	, mOffset(offset)
	, mVelocity(INITIAL_BALL_VELOCITY)
{ // create this->amount default particle instances
    for (unsigned int i = 0; i < this->mAmount; ++i)
    {
        auto particle = std::make_shared<Particle>(texture);
        this->mParticles.push_back(particle);
        mParticlesLifecycle[particle] = 0.0f;
    }
}

void ParticleGenerator::Update(float elapsedTime)
{
    // sTime += elapsedTime;
    // if (sTime > 0.1f)
    // {
        // add new particles 
        for (unsigned int i = 0; i < mNewParticles; ++i)
        {
            const auto& unusedParticle = firstUnusedParticle();
            this->respawnParticle(unusedParticle, mAttachObj, mOffset);
        }
        // update all particles
        for (const auto& particle : mParticles)
        {
            mParticlesLifecycle[particle] -= elapsedTime;// reduce life
            if (mParticlesLifecycle[particle] > 0.0f)
            {	// particle is alive, thus update
                auto ballObj = std::dynamic_pointer_cast<Ball>(mAttachObj);
                if (ballObj)
                {
                    mVelocity = ballObj->GetVelocity();
                }
                particle->SetPosX(particle->GetPosX() - mVelocity.x() * elapsedTime);
                particle->SetPosY(particle->GetPosY() - mVelocity.y() * elapsedTime);
                particle->SetColorAlpha(particle->GetColor()[3] - 2.5f * elapsedTime);
            }
        }
    //     sTime = 0.0f;
    // }
}

void ParticleGenerator::OnRender()
{
    for(const auto& particle : mParticles)
    {
        if (mParticlesLifecycle[particle] > 0.0f)
        {
            g_pGraphicsManager->GetParticleRenderer()->AddParticle(particle);
        }
    }
}

std::shared_ptr<Particle> ParticleGenerator::firstUnusedParticle()
{
    for (size_t i = LastUsedParticleIndex; i < mAmount; i++)
    {
        if (mParticlesLifecycle[mParticles[i]] <= 0.0f)
        {
            LastUsedParticleIndex = i;
            // Logger::LogInfo(std::format("LastUsedParticleIndex = {}", i));
            return mParticles[LastUsedParticleIndex];
        }
    }

    for (size_t i = 0; i < mAmount; i++)
    {
	    if (mParticlesLifecycle[mParticles[i]] <= 0.0f)
	    {
            LastUsedParticleIndex = i;
            return mParticles[LastUsedParticleIndex];
	    }
    }
    LastUsedParticleIndex = 0;
    return mParticles[LastUsedParticleIndex];
}

void ParticleGenerator::respawnParticle(std::shared_ptr<Particle> particle, std::shared_ptr<GameObject> attachObject, Eigen::Vector2f offset)
{
    auto obj = std::dynamic_pointer_cast<RenderableObject>(attachObject);
    float random = ((rand() % 100) - 50) / 10.0f;
    float rColor = 0.5f + ((rand() % 100) / 100.0f);

    if (std::find(mParticles.begin(), mParticles.end(), particle) != mParticles.end())
    {
        particle->SetPosX(obj->GetPosX() + random + offset.x());
        particle->SetPosY(obj->GetPosY() + random + offset.y());
        particle->SetColor(Eigen::Vector4f(rColor, rColor, rColor, 1.0f));
        mParticlesLifecycle[particle] = 1.0f;
    }
}
