#include "Brick.h"

Brick::Brick(std::string texture, int xpos, int ypos, int xsize, int ysize, Eigen::Vector3f color)
	: RenderableObject(texture, xpos, ypos, xsize, ysize, color)
{
}