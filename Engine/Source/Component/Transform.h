#pragma once
#include <Eigen/core>
#include "IComponent.h"
class Transform :public IComponent
{
public:
	Transform();


	void Update() override {}
	std::string GetTypeName() override { return "Transform"; }

	Eigen::Vector3f mPosition;
	float mRotation;
	Eigen::Vector3f mScaler;
};