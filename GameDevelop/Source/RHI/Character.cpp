#include "Character.h"

Character::Character(unsigned int texture, Eigen::Vector2i size, Eigen::Vector2i bearing, long advance)
	:mTexture(texture),
	mSize(size),
	mBearing(bearing),
	mAdvance(advance)
{
}

Character::Character()
	:mTexture(0),
	mAdvance(0)
{
}

Character::Character(Character& ch)
{
	this->mTexture = ch.mTexture;
	this->mBearing = ch.mBearing;
	this->mSize = ch.mSize;
	this->mAdvance = ch.mAdvance;
}
