#pragma once
#include "Entities/RenderableObject.h"
class Wall : public RenderableObject
{
public:
	Wall();
	Wall(std::string texture, int xpos = 0, int ypos = 0, int xsize = 50, int ysize = 50);
	~Wall();

private:
	int x, y;
};