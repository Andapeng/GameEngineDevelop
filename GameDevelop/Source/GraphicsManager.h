#pragma once
#include "IManager.h"
class GraphicsManager :
	public IManager
{
public:
	GraphicsManager() {};
	virtual int Initialize() { return 1; };
	virtual void Release() {};
	virtual void Tick() {};
};
