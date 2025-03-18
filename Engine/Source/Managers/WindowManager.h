#pragma once
#include <vector>

#include "IManager.h"
namespace sadp
{
	class IWindow;
}

class WindowManager : public IManager
{
public:
	static WindowManager* Get();

	// Í¨¹ý IManager ¼Ì³Ð
	virtual int Initialize() override;
	virtual void Release() override;
	virtual void Tick() override;

	void RegisterWindow(sadp::IWindow* Window, bool IsMainWindow);
	int GetMainWindowHandle();
	void GetMainWindowSize(int& x, int &y);
	sadp::IWindow* GetMainWindow();
private:
	WindowManager();
	static WindowManager* mWindowMgr;

	sadp::IWindow* mMainWindow = nullptr;
	std::vector<sadp::IWindow*> mWindowHwnds;
};

extern WindowManager* g_pWindowManager;