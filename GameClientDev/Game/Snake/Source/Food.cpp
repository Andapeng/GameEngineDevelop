#include "Food.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include "Snake.h"
#include "Entities/RenderableObject.h"

Food::Food()
	: ::RenderableObject(),
	  x(0),
	  y(0)
{
}

Food::Food(std::string texture, int xpos, int ypos, int xsize, int ysize)
	:RenderableObject(texture, xpos, ypos, xsize, ysize)
{
	srand((unsigned)time(NULL));
	x = rand() % 16;
	y = rand() % 12;
	SetPosition(x*50, y*50, 0);
}

Food::~Food()
{
}

void Food::Produce(Snake* snake)
{
	srand((unsigned)time(NULL));
	x = rand() % 16;
	y = rand() % 12;
	while (snake->IsContain(x * 50, y * 50)) {
		x = rand() % 16;
		y = rand() % 12;
	}
	SetPosition(x * 50, y * 50, 0);
}
