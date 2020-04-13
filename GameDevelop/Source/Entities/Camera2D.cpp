#include "Camera2D.h"

Camera2D::Camera2D(int width, int height)
	:mWidth(width),
	mHeight(height)
{
	mProjectMatrix = Ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
}

Eigen::Matrix4f Camera2D::GetProjectMatrix()
{
	return mProjectMatrix;
}
