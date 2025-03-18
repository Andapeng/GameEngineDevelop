#include "WindowManager.h"

#include "../Platform/IWindow.h"

WindowManager* WindowManager::mWindowMgr = nullptr;

WindowManager* WindowManager::Get()
{
    if (mWindowMgr == nullptr)
    {
        mWindowMgr = new WindowManager();
    }
    return mWindowMgr;
}

int WindowManager::Initialize()
{
    return 0;
}

void WindowManager::Release()
{
}

void WindowManager::Tick()
{
}

void WindowManager::RegisterWindow(sadp::IWindow* Window,bool IsMainWindow)
{
    mWindowHwnds.push_back(Window);
    if (IsMainWindow)
    {
        mMainWindow = Window;
    }
}

int WindowManager::GetMainWindowHandle()
{
    return mMainWindow->GetHandle();
}

void WindowManager::GetMainWindowSize(int& x, int& y)
{
    mMainWindow->GetSize(x, y);
}

sadp::IWindow* WindowManager::GetMainWindow()
{
    return mMainWindow;
}

WindowManager::WindowManager()
{
}
