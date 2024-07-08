#pragma once
#include "../../GameInstance.h"
class Breakout : public GameInstance
{
	virtual int Initialize() override;
	virtual int Tick() override;
	virtual int Release() override;

	// manage event
	virtual void ProcessInput() override;

	// manage render
	virtual void Render() override;

	// game state update
	virtual void Update(float elapsedTime) override;

	// manage physics
	virtual void DetectCollide() override;
private:

};