#include "IManager.h"
#include <map>
#include <string>
class InputManager : public IManager
{
public:
	virtual int Initialize () override;
	virtual void Tick() override;
	virtual void Release() override;

	static InputManager* Get();

	bool IsKeyPressed(std::string keyString);
	void KeyPressed(int code);
	void KeyRelease(int code);
private:

	InputManager() {};
	std::map<int, std::string> mKeyToStringMap;
	std::map<std::string, int> mStringToKeyMap;
	std::map<int, bool> mKeyPressed;
	static InputManager* mSingleInputManager;

};

extern InputManager* g_pInputManager;