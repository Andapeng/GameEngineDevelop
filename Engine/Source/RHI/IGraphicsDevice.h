#pragma once

class IGraphicsDevice
{
public:
	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};