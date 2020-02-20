#pragma once
#include <sfml/Graphics.hpp>
class GameObject
{
public:
	GameObject();
	int GetTexture()const { return mTexture; }

protected:
private:
	int mID;
	int mTexture;
	int xPos;
	int yPos;
};