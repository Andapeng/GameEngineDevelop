#include "Math.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
Eigen::Matrix4f LookAt()
{
	return Eigen::Matrix4f();
}

Eigen::Matrix4f Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
	result(0, 0) = 2 / (right - left);
	result(1, 1) = 2 / (top - bottom);
	result(2, 2) = -2 / (zFar - zNear);
	result(0, 3) = -(right + left) / (right - left);
	result(1, 3) = -(top + bottom) / (top - bottom);
	result(2, 3) = -(zFar + zNear) / (zFar - zNear);
	return result;
}

Eigen::Matrix4f Perspective()
{
	return Eigen::Matrix4f();
}

Eigen::Matrix4f Translate(Eigen::Matrix4f& mat, Eigen::Vector3f vec)
{
	mat(0, 3) += vec(0);
	mat(1, 3) += vec(1);
	mat(2, 3) += vec(2);
	return mat;
}

Eigen::Matrix4f Rotate()
{
	return Eigen::Matrix4f();
}

Eigen::Matrix4f Scale(Eigen::Matrix4f& mat, Eigen::Vector3f scaler)
{
	mat(0, 0) *= scaler(0);
	mat(1, 1) *= scaler(1);
	mat(2, 2) *= scaler(2);
	return mat;
}