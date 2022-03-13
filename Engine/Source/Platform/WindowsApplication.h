#pragma once
#include <Windows.h>
#include "IApplication.h"
class WindowsMessageHandler;
class WindowsWindow;

class WindowsApplication
{
public:
	

	static WindowsApplication* CreateWindowsApplication(const HINSTANCE HInstance);


protected:
	int ProcessMessage(HWND hwnd, UINT32 msg, WPARAM wParam, LPARAM lParam);
private:

	bool Register(const HINSTANCE HInstance);
	static LRESULT CALLBACK AppWndProc(HWND hwnd, UINT32 msg, WPARAM wParam, LPARAM lParam);

	WindowsApplication(const HINSTANCE HInstance);
private:
	HINSTANCE InstanceHandle;
	WindowsMessageHandler* MessageHandler;
	WindowsWindow* Window;
	

};

