#pragma once
#include <Eigen/Core>
class Character
{
public:
	Character(unsigned int texture, Eigen::Vector2i size, Eigen::Vector2i bearing, long advance);
	Character();
	Character(Character& ch);
	unsigned int GetTexture() const {	return mTexture;}
	Eigen::Vector2i GetSize() const { return mSize; }
	Eigen::Vector2i GetBearing() const { return mBearing; }
	long GetAdvance() const { return mAdvance; }
private:
	unsigned int mTexture;
	Eigen::Vector2i mSize;
	Eigen::Vector2i mBearing;
	long mAdvance;

};