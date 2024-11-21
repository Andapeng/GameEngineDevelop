#include "OpenGLGraphicsDevice.h"
#include "../Log.h"
#include "GLAD/glad.h"
OpenGLGraphicsDevice::OpenGLGraphicsDevice()
{
	if (!gladLoadGL()) {
		exit(-1);
		Logger::LogError("load gl failed!");
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

OpenGLGraphicsDevice::~OpenGLGraphicsDevice()
{
}
