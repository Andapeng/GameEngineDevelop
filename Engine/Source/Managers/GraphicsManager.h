#pragma once
#include "IManager.h"
class PostProcessingRenderer;
class ParticleRenderer;
class ImguiRenderer;
class IGraphicsDevice;
class VulkanGrahphicsDevice;
class D3D12GraphicsDevice;
class OpenGLGraphicsDevice;
class TextRenderer;
class SpriteRenderer;

class GraphicsManager :
	public IManager
{
public:
	

	static GraphicsManager* Get();

	virtual int Initialize() override;
	virtual void Release() override ;
	virtual void Tick() override;

	SpriteRenderer* GetSpriteRenderer() { return mSpriteRenderer; }
	TextRenderer* GetTextRenderer() { return mTextRenderer; }
	ImguiRenderer* GetImguiRenderer() { return mImguiRenerer; }
	ParticleRenderer* GetParticleRenderer() { return mParticleRenderer; }
	PostProcessingRenderer* GetPostProcessingRenderer() { return mPostProcessingRenderer; }

	int ProcessDrawCommnad();

	void Draw();

private:
	GraphicsManager();
	static GraphicsManager* mSingleGraphicsManager;
	SpriteRenderer* mSpriteRenderer;
	TextRenderer* mTextRenderer;
	ImguiRenderer* mImguiRenerer;
	ParticleRenderer* mParticleRenderer;
	PostProcessingRenderer* mPostProcessingRenderer;

	IGraphicsDevice* mGrahpicsDevice;	
};

extern GraphicsManager* g_pGraphicsManager;
