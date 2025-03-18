#pragma once
#include "../RHI/Texture.h"

class PostProcessingRenderer
{
public:
	int Initialize();
	int Release();
	void BeginRender();
	void EndRender();
	void OnRender();

	bool IsChaos() { return mChaos; }
	bool IsConfuse() { return mConfuse; }

	void SetShake(bool bShake);
	void SetChaos(bool bChaos) { mChaos = bChaos; }
	void SetConfuse(bool bConfuse) { mConfuse = bConfuse; }
private:
	// options
	bool mConfuse = false;
	bool mChaos = false;
	bool mShake = false;
	// render state
	unsigned int MSFBO, FBO; // MSFBO = Multisampled FBO. FBO is regular, used for blitting MS color-buffer to texture
	unsigned int RBO; // RBO is used for multisampled color buffer
	unsigned int VAO;

	int mWidth, mHeight;

	Texture2D mTexture;

};