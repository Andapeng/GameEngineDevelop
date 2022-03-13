#include "WindowsApplication.h"
#include "WindowsMessageHandler.h"
WindowsApplication* OwnWindowsApplication = nullptr;

int WindowsApplication::ProcessMessage(HWND hwnd, UINT32 msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		const INT32 Win32Key = static_cast<const INT32>(wParam);
		switch (Win32Key)
		{
		case -1:
			break;
		default:
			MessageHandler->OnKeyDown();
			break;
		}
	}
		break;
	case WM_KEYUP:
		break;
	default:
		break;
	}
	return 0;
}

WindowsApplication* WindowsApplication::CreateWindowsApplication(const HINSTANCE HInstance)
{
	OwnWindowsApplication = new WindowsApplication(HInstance);
	return OwnWindowsApplication;
}

bool WindowsApplication::Register(const HINSTANCE HInstance)
{


	WNDCLASS wc;

	memset(&wc, 0, sizeof(wc));

	wc.style = CS_DBLCLKS; // We want to receive double clicks

	wc.lpfnWndProc = AppWndProc;

	wc.cbClsExtra = 0;

	wc.cbWndExtra = 0;

	wc.hInstance = HInstance;

	wc.hCursor = NULL;	// We manage the cursor ourselves

	wc.hbrBackground = NULL; // Transparent

	wc.lpszMenuName = NULL;


	if (!::RegisterClass(&wc))

	{

		//ShowLastError();



		// @todo Slate: Error message should be localized!

		MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);



		return false;

	}


	return true;
}

LRESULT WindowsApplication::AppWndProc(HWND hwnd, UINT32 msg, WPARAM wParam, LPARAM lParam)
{
	return OwnWindowsApplication->ProcessMessage(hwnd, msg, wParam, lParam);
}

WindowsApplication::WindowsApplication(const HINSTANCE HInstance)
	:InstanceHandle(HInstance)
	,MessageHandler(new WindowsMessageHandler)
{
}
