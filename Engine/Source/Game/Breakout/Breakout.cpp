#include "Breakout.h"
#include "../../Managers/Managers.h"

#include <GLAD/glad.h>
#include "../../RHI/Shader.h"
#include "../../RHI/Texture.h"
#include "../../RHI/Character.h"

#include "../../Math/Math.h"

#include "../../Entities/GameObject.h"
#include "../../Entities/RenderableObject.h"
#include "../../Entities/Player.h"

#include <iostream>
#include "../../Network/NetworkClient.h"


int Breakout::Initialize()
{
	// Managers Initializing
	GameInstance::Initialize();

	return 0;
}

int Breakout::Tick()
{
	return 0;
}

int Breakout::Release()
{
	return 0;
}

void Breakout::ProcessInput()
{
}

void Breakout::Render()
{
}

void Breakout::Update(float elapsedTime)
{
}

void Breakout::DetectCollide()
{
}
