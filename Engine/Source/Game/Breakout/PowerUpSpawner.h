#pragma once
#include <memory>
#include <vector>
#include "../../Entities/RenderableObject.h"
class GameObject;
class PowerUp;

class PowerUpSpawner : public RenderableObject
{
public:

	virtual void Update(float elapsedTime) override;

	void SpawnPowerUps(std::shared_ptr<RenderableObject> block);
	void UpdatePowerUps(float dt);
	std::vector<std::shared_ptr<PowerUp>> GetPowerUps() { return mPowerUps; }
	void ActivatePowerUp(std::shared_ptr<PowerUp> powerUp);

	void OnRender() override;

private:
	bool ShouldSpawn(unsigned int chance);
	bool IsOtherPowerUpActive(std::string type);

	std::vector< std::shared_ptr<PowerUp>>  mPowerUps;
	std::shared_ptr<PowerUp> mCurrentActivatedPowerUp;
};
