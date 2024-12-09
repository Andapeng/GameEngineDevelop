#include "Physics2D.h"

/*
int CheckCollision(int One_x1, int One_y1, int One_x2, int One_y2, int Two_x1, int Two_y1, int Two_x2, int Two_y2)
{
	bool xIsCollide = (One_x1 < Two_x1) && (One_x2 > Two_x2);
	bool yIsCollide = (One_y1 < Two_y1) && (One_y2 > Two_y2);
	return xIsCollide && yIsCollide;
}

int CheckCollision(Collider2D& collider1, Collider2D& collider2)
{
	return CheckCollision(collider1.x1, collider1.y1, collider1.x2, collider1.y2, collider2.x1, collider2.y1, collider2.x2, collider2.y2);
}
*/
bool CheckCollision(std::shared_ptr<RenderableObject> one, std::shared_ptr<RenderableObject> two)
{
    // collision x-axis?
    bool collisionX = one->GetPosX() + one->GetSizeX() >= two->GetPosX() &&
        two->GetPosX() + two->GetSizeX() >= one->GetPosX();
    // collision y-axis?
    bool collisionY = one->GetPosY() + one->GetSizeX() >= two->GetPosY() &&
        two->GetPosY() + two->GetSizeY() >= one->GetPosY();
    // collision only if on both axes
    return collisionX && collisionY;
}

Direction VectorDirection(Eigen::Vector2f closest)
{
    Eigen::Vector2f compass[] = {
     Eigen::Vector2f(0.0f, 1.0f),	// up
     Eigen::Vector2f(1.0f, 0.0f),	// right
     Eigen::Vector2f(0.0f, -1.0f),	// down
     Eigen::Vector2f(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    closest.normalize();
    for (unsigned int i = 0; i < 4; i++)
    {
        float dotProduct = closest.dot( compass[i]);
        if (dotProduct > max)
        {
            max = dotProduct;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
