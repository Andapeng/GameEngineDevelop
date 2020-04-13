#include "GraphicsManager.h"
#include <GLAD/glad.h>

#include <cstdlib>
#include <iostream>

#include "../Renderer/SpriteRenderer.h"
#include "../Renderer/TextRenderer.h"

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

	mSpriteRenderer = new SpriteRenderer;
	mTextRenderer = new TextRenderer;

	mSpriteRenderer->Initialize();
	mTextRenderer->Initialize();

	return 1;
}

void GraphicsManager::Release()
{
	mSpriteRenderer->Release();
	mTextRenderer->Release();

	delete mSpriteRenderer;
	delete mTextRenderer;

	delete mSingleGraphicsManager;

		
}

void GraphicsManager::Draw()
{
}

GraphicsManager::GraphicsManager()
	:mSpriteRenderer(nullptr),
	mTextRenderer(nullptr)
{

}