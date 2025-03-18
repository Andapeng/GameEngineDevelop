#include "PowerUpSpawner.h"

#include "Ball.h"
#include "Paddle.h"
#include "PowerUp.h"
#include "../../Managers/SceneManager.h"
#include "../../Managers/GraphicsManager.h"
#include "../../Renderer/PostProcessingRenderer.h"
#include "../../Scene/Scene.h"

void PowerUpSpawner::Update(float elapsedTime)
{
    auto BallObj = dynamic_pointer_cast<Ball>(g_pSceneManager->GetCurrentScene()->GetGameObject("ball"));
    auto PaddleObj = dynamic_pointer_cast<Paddle>(g_pSceneManager->GetCurrentScene()->GetGameObject("paddle"));
    auto PostProcessor = g_pGraphicsManager->GetPostProcessingRenderer();

    for (auto powerUp : mPowerUps)
    {
        powerUp->Update(elapsedTime);

        if (!powerUp->IsActivated())
        {
            // deactivate effects
            if (powerUp->GetType() == "sticky")
            {
                if (!IsOtherPowerUpActive("sticky"))
                {	// only reset if no other PowerUp of type sticky is active
                    BallObj->SetSticky(false);
                    PaddleObj->SetColor(Eigen::Vector3f{1.0f, 1.0f, 1.0f});
                }
            }
            else if (powerUp->GetType() == "pass-through")
            {
                if (!IsOtherPowerUpActive("pass-through"))
                {	// only reset if no other PowerUp of type pass-through is active
                    BallObj->SetPassThrough(false);
                    BallObj->SetColor(Eigen::Vector3f{1.0f, 1.0f, 1.0f});
                }
            }
            else if (powerUp->GetType() == "confuse")
            {
                if (!IsOtherPowerUpActive("confuse"))
                {	// only reset if no other PowerUp of type confuse is active
                    PostProcessor->SetConfuse(false);
                }
            }
            else if (powerUp->GetType() == "chaos")
            {
                if (!IsOtherPowerUpActive("chaos"))
                {	// only reset if no other PowerUp of type chaos is active
                    PostProcessor->SetChaos(false);
                }
            }
        }
    }
    this->mPowerUps.erase(std::remove_if(this->mPowerUps.begin(), this->mPowerUps.end(),
        [](const auto powerUp) { return powerUp->IsDestroyed() && !powerUp->IsActivated(); }
    ), this->mPowerUps.end());
}

void PowerUpSpawner::SpawnPowerUps(std::shared_ptr<RenderableObject> block)
{
    if (ShouldSpawn(75)) // 1 in 75 chance
        this->mPowerUps.push_back(
            std::make_shared<PowerUp>("speed", Eigen::Vector3f(0.5f, 0.5f, 1.0f), 0.0f, block->GetPosition2D(), "powerup_speed"
            ));
    else if (ShouldSpawn(75))
        this->mPowerUps.push_back(
            std::make_shared <PowerUp>("sticky", Eigen::Vector3f(1.0f, 0.5f, 1.0f), 20.0f, block->GetPosition2D(), "powerup_sticky")
            );
    else if (ShouldSpawn(75))
        this->mPowerUps.push_back(
            std::make_shared<PowerUp>("pass-through", Eigen::Vector3f(0.5f, 1.0f, 0.5f), 10.0f, block->GetPosition2D(), "powerup_passthrough"
            ));
    else if (ShouldSpawn(75))
        this->mPowerUps.push_back(
            std::make_shared<PowerUp>("pad-size-increase", Eigen::Vector3f(1.0f, 0.6f, 0.4), 0.0f, block->GetPosition2D(), "powerup_increase"
            ));
    else if (ShouldSpawn(15)) // negative powerups should spawn more often
        this->mPowerUps.push_back(
            std::make_shared<PowerUp>("confuse", Eigen::Vector3f(1.0f, 0.3f, 0.3f), 15.0f, block->GetPosition2D(), "powerup_confuse"
            ));
    else if (ShouldSpawn(15))
        this->mPowerUps.push_back(
            std::make_shared<PowerUp>("chaos", Eigen::Vector3f(0.9f, 0.25f, 0.25f), 15.0f, block->GetPosition2D(), "powerup_chaos"
            ));
}

void PowerUpSpawner::UpdatePowerUps(float dt)
{
}

void PowerUpSpawner::ActivatePowerUp(std::shared_ptr<PowerUp> powerUp)
{
    powerUp->SetActivated(true);
    powerUp->SetDestroyed(true);
    auto BallObj = dynamic_pointer_cast<Ball>(g_pSceneManager->GetCurrentScene()->GetGameObject("ball"));
    auto PaddleObj = dynamic_pointer_cast<Paddle>(g_pSceneManager->GetCurrentScene()->GetGameObject("paddle"));
    auto PostProcessor = g_pGraphicsManager->GetPostProcessingRenderer();

    if (powerUp->GetType() == "speed")
    {
        BallObj->SetVelocity(BallObj->GetVelocity() * 1.2);
    }
    else if (powerUp->GetType() == "sticky")
    {
        BallObj->SetSticky(true);
        PaddleObj->SetColor(Eigen::Vector3f(1.0f, 0.5f, 1.0f));
    }
    else if (powerUp->GetType() == "pass-through")
    {
        BallObj->SetPassThrough(true);
        BallObj->SetColor(Eigen::Vector3f(1.0f, 0.5f, 0.5f));
    }
    else if (powerUp->GetType() == "pad-size-increase")
    {
        PaddleObj->SetSize({ PaddleObj->GetSizeX() + 50, PaddleObj->GetSizeY() });
    }
    else if (powerUp->GetType() == "confuse")
    {
        if (!PostProcessor->IsChaos())
            PostProcessor->SetConfuse(true); // only activate if chaos wasn't already active
    }
    else if (powerUp->GetType() == "chaos")
    {
        if (!PostProcessor->IsConfuse())
            PostProcessor->SetChaos(true);
    }
    mCurrentActivatedPowerUp = powerUp;
}

void PowerUpSpawner::OnRender()
{
    for (const auto& powerUp : this->mPowerUps)
    {
        powerUp->OnRender();
    }
}

bool PowerUpSpawner::ShouldSpawn(unsigned chance)
{
    unsigned int random = rand() % chance;
    return random == 0;
}

bool PowerUpSpawner::IsOtherPowerUpActive(std::string type)
{
    for (const auto& powerUp : mPowerUps)
    {
        if (powerUp->IsActivated())
            if (powerUp->GetType() == type)
                return true;
    }
    return false;
}
