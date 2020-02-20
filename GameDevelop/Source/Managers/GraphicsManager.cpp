#include "GraphicsManager.h"
#include <GLAD/glad.h>

#include <cstdlib>
#include <iostream>

GraphicsManager* GraphicsManager::mSingleGraphicsManager = nullptr;

GraphicsManager* GraphicsManager::Get()
{
	if (mSingleGraphicsManager == nullptr)
	{
		mSingleGraphicsManager = new GraphicsManager;
	}
	return mSingleGraphicsManager;
}

int GraphicsManager::Initialize()
{
	if (!gladLoadGL()) {
		exit(-1);
		std::cout << "load gl failed!" << std::endl;
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 1;
}