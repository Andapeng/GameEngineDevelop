#pragma once
#include "IManager.h"
class ResourceManager : public IManager
{
public:
	virtual int Initialize() { return 1; }
	virtual void Tick() {}
	virtual void Release() {}

};