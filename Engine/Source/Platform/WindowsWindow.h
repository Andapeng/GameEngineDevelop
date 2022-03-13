#pragma once
#include "IWindow.h"
class WindowsWindow : public IWindow
{
public:
	int Create() override;

	void Show() override;

	void ProcessEvent() override;
};