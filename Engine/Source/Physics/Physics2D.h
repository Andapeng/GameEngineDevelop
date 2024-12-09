#pragma once
#include "../Entities/RenderableObject.h"
/*
class Collider2D
{
public:

private:
	int x1;
	int x2;
	int y1;
	int y2;
};

int CheckCollision(Collider2D& collider1, Collider2D& collider2);
*/
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
typedef std::tuple<bool, Direction, Eigen::Vector2f> Collision;
// collision detection
bool CheckCollision(std::shared_ptr<RenderableObject> one, std::shared_ptr<RenderableObject> two);
Direction VectorDirection(Eigen::Vector2f closest);