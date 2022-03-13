#pragma once
#include <Eigen/Core>

Eigen::Matrix4f Translate(Eigen::Matrix4f& mat, Eigen::Vector3f vec);
Eigen::Matrix4f Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
Eigen::Matrix4f Ortho(float left, float right, float bottom, float top);
Eigen::Matrix4f Scale(Eigen::Matrix4f& mat, Eigen::Vector3f scaler);