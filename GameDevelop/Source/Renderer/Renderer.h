#pragma once
#include "../Math/Math.h"
class Texture2D;

class Renderer
{
public:
	void Initialize();
	void TestRender();
	void Release();

	void ClearColor();
private:

	unsigned int VBO, VAO, EBO;
};