#include "InputManager.h"
//#include <Windows.h>
#include <SFML/Window.hpp>

InputManager* InputManager::mSingleInputManager = nullptr;

int InputManager::Initialize()
{
	//KeyMap[VK_UP] = "Up";
	//KeyMap[VK_DOWN] = "Down";
	//KeyMap[VK_LEFT] = "Left";
	//KeyMap[VK_RIGHT] = "Right";
	//KeyMap[VK_SPACE] = "Space";
	mStringToKeyMap["Space"] = sf::Keyboard::Key::Space;
	mStringToKeyMap["Enter"] = sf::Keyboard::Key::Enter;
	mStringToKeyMap["Up"] = sf::Keyboard::Key::Up;
	mStringToKeyMap["Down"] = sf::Keyboard::Key::Down;
	mStringToKeyMap["Left"] = sf::Keyboard::Key::Left;
	mStringToKeyMap["Right"] = sf::Keyboard::Key::Right;
	return 1;
}

void InputManager::Tick()
{


}

void InputManager::Release()
{
	mKeyPressed.clear();
	mKeyToStringMap.clear();
	mStringToKeyMap.clear();
	delete mSingleInputManager;

}

InputManager* InputManager::Get()
{
	if (mSingleInputManager == nullptr)
	{
		mSingleInputManager = new InputManager;
	}
	return mSingleInputManager;
}

bool InputManager::IsKeyPressed(std::string keyString)
{
	int code = mStringToKeyMap[keyString];
	bool result = mKeyPressed[code];
	mKeyPressed[code] = false;
	return result;
}

void InputManager::KeyPressed(int code)
{
	mKeyPressed[code] = true;
}

void InputManager::KeyRelease(int code)
{
	mKeyPressed[code] = false;
}
