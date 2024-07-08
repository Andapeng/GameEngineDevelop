#pragma once
#include "../../Entities/RenderableObject.h"
class Snake;
class Food : public RenderableObject
{
public:
	Food();
	Food(std::string texture, int xpos = 0, int ypos = 0, int xsize = 50, int ysize = 50);
	~Food() override;
	void Produce(Snake* snake);
private:

	int x;
	int y;
};