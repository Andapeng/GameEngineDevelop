#pragma once
#include "IManager.h"
class GraphicsManager :
	public IManager
{
public:
	

	static GraphicsManager* Get();

	virtual int Initialize() override;
	virtual void Release() override {};
	virtual void Tick() override {};

private:
	GraphicsManager() {};
	static GraphicsManager* mSingleGraphicsManager;
};
