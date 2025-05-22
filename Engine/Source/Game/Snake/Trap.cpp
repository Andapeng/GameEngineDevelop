#include "Trap.h"


Trap::Trap(std::string texture, int xpos, int ypos, int xsize, int ysize)
	:RenderableObject(texture, xpos, ypos,0.01f, xsize, ysize)
{
}

Trap::~Trap() {}
