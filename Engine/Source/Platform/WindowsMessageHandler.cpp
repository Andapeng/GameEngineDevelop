#include "WindowsMessageHandler.h"
#include <iostream>
bool WindowsMessageHandler::OnKeyDown()
{
	std::cout << "press one key" << std::endl;
	return false;
}

WindowsMessageHandler::WindowsMessageHandler()
{
}
