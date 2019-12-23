#include "IManager.h"
class InputManager : public IManager
{
public:
	virtual int Initialize() { return 1; }
	virtual void Tick() {}
	virtual void Release() {}
};