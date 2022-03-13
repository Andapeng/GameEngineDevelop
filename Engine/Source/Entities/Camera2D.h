#pragma once
#include "../Math/Math.h"
class Camera2D
{
public:
	Camera2D(int width, int height);
	Eigen::Matrix4f GetProjectMatrix();
private:
	int mWidth;
	int mHeight;
	Eigen::Matrix4f mProjectMatrix;
};