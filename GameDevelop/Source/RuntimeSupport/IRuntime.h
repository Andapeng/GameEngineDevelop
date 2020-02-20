#pragma once
class IRuntime
{
public:
	virtual int Initialize();
	virtual void Tick();
	virtual void Release();
};