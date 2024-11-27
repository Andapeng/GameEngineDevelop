#include "OpenGLGraphicsDevice.h"
#include "../Log.h"
#include "GLAD/glad.h"
#include "../Managers/WindowManager.h"
#include "../Platform/IWindow.h"

OpenGLGraphicsDevice::OpenGLGraphicsDevice()
{

}

OpenGLGraphicsDevice::~OpenGLGraphicsDevice()
{
}

void OpenGLGraphicsDevice::Initialize()
{
	if (!gladLoadGL()) {
		exit(-1);
		Logger::LogError("load gl failed!");
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLGraphicsDevice::Release()
{
}

void OpenGLGraphicsDevice::Draw()
{
	
}
