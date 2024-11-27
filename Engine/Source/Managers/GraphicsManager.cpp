#include "GraphicsManager.h"
#include <GLAD/glad.h>

#include <cstdlib>
#include <iostream>

#include "../Renderer/SpriteRenderer.h"
#include "../Renderer/TextRenderer.h"

#include "../RHI/D3D12GraphicsDevice.h"
#include "../RHI/VulkanGraphicsDevice.h"
#include "../RHI/OpenGLGraphicsDevice.h"
#include "../RHI/IGraphicsDevice.h"

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
	mGrahpicsDevice = new OpenGLGraphicsDevice;
	// mVulkanDevice = new VulkanGrahphicsDevice;
	// mD3D12Device = new D3D12GraphicsDevice;

	mGrahpicsDevice->Initialize();
	// mVulkanDevice->Initialize();
	// mD3D12Device->Initialize();

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

	mGrahpicsDevice->Release();
	delete mGrahpicsDevice;

	delete mSingleGraphicsManager;

		
}

void GraphicsManager::Tick()
{
	// mVulkanDevice->Draw();
	// mD3D12Device->Draw();
}

void GraphicsManager::Draw()
{
}

GraphicsManager::GraphicsManager()
	:mSpriteRenderer(nullptr),
	mTextRenderer(nullptr)
{

}