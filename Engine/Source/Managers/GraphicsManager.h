#pragma once
#include "IManager.h"
class TextRenderer;
class SpriteRenderer;

class GraphicsManager :
	public IManager
{
public:
	

	static GraphicsManager* Get();

	virtual int Initialize() override;
	virtual void Release() override ;
	virtual void Tick() override {};

	SpriteRenderer* GetSpriteRenderer() { return mSpriteRenderer; }
	TextRenderer* GetTextRenderer() { return mTextRenderer; }

	int ProcessDrawCommnad();

	void Draw();

private:
	GraphicsManager();
	static GraphicsManager* mSingleGraphicsManager;
	SpriteRenderer* mSpriteRenderer;
	TextRenderer* mTextRenderer;
	
};

extern GraphicsManager* g_pGraphicsManager;
