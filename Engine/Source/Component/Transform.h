#pragma once
#include <Eigen/core>
#include "IComponent.h"
class Transform :public IComponent
{
public:
	Transform();

	virtual int GetType() { return 1; }
	virtual bool IsType() { return true; }
	virtual void Update() {}

	Eigen::Vector3f mPosition;
	float mRotation;
	Eigen::Vector3f mScaler;
};