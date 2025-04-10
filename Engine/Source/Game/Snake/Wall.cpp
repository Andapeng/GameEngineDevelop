#include "Wall.h"


Wall::Wall(std::string texture, int xpos, int ypos, int xsize, int ysize)
	:RenderableObject(texture, xpos, ypos,0.01f, xsize, ysize)
{
}

Wall::~Wall()
{
}
