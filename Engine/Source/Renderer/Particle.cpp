#include "Particle.h"

Particle::Particle(std::string texture, Eigen::Vector3f pos, Eigen::Vector2f size, Eigen::Vector4f color)
	: mTexture(texture),
	  mPos(pos),
	  mSize(size),
	  mColor(color)
{
}
