#include "InputManager.h"
#include <Windows.h>

int InputManager::Initialize()
{
	KeyMap[VK_UP] = "Up";
	KeyMap[VK_DOWN] = "Down";
	KeyMap[VK_LEFT] = "Left";
	KeyMap[VK_RIGHT] = "Right";
	KeyMap[VK_SPACE] = "Space";

	return 1;
}

void InputManager::Tick()
{


}

void InputManager::Release()
{

}