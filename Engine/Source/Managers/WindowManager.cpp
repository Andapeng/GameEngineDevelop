#include "WindowManager.h"

#include "../Platform/IWindow.h"

WindowManager* WindowManager::m_WindowMgr = nullptr;

WindowManager* WindowManager::Get()
{
    if (m_WindowMgr == nullptr)
    {
        m_WindowMgr = new WindowManager();
    }
    return m_WindowMgr;
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
    m_WindowHwnds.push_back(Window);
    if (IsMainWindow)
    {
        m_MainWindow = Window;
    }
}

int WindowManager::GetMainWindowHandle()
{
    return m_MainWindow->GetHandle();
}

void WindowManager::GetMainWindowSize(int& x, int& y)
{
    m_MainWindow->GetSize(x, y);
}

sadp::IWindow* WindowManager::GetMainWindow()
{
    return m_MainWindow;
}

WindowManager::WindowManager()
{
}
