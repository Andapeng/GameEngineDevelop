#include "Wall.h"

Wall::Wall()
	:RenderableObject(),
	x(0),
	y(0)
{
}

Wall::Wall(std::string texture, int xpos, int ypos, int xsize, int ysize)
	:RenderableObject(texture, xpos, ypos, xsize, ysize),
	x(xpos),
	y(ypos)
{
	SetPosition(x * 50, y * 50, 0);
}

Wall::~Wall()
{
}
