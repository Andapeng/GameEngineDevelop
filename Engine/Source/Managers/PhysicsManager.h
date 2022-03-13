#pragma once
#include "IManager.h"
class b2World;

class PhysicsManager
	: public IManager
{
public:
	int Initialize() override;
	void Tick() override;
	void Release() override;

	static PhysicsManager* Get();

private:
	b2World* m2DWorld;

	static PhysicsManager* mSinglePhysicsManager;
};

extern PhysicsManager* g_pPhysicsManager;