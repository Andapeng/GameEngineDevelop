#pragma once
class IManager
{
public:
	virtual int Initialize() = 0;
	virtual void Release() = 0;
	virtual void Tick() = 0;
};

