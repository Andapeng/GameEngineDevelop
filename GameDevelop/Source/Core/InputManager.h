#include "../Managers/IManager.h"
#include <map>
#include <string>
class InputManager : public IManager
{
public:
	virtual int Initialize () override;
	virtual void Tick() override;
	virtual void Release() override;

	std::string GetKeyFromCode(int code){ return KeyMap[code]; }
private:
	std::map<int, std::string> KeyMap;
};