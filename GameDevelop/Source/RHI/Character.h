#pragma once
#include <Eigen/Core>
class Character
{

private:
	unsigned int mTexture;
	Eigen::Vector2i mSize;
	Eigen::Vector2i mBearing;
	unsigned int mAdvance;
};