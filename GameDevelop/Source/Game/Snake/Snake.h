#pragma once
#include "../../Entities/RenderableObject.h"
#include <list>
#include "Food.h"
class Snake : public RenderableObject
{
public:
	Snake();
	Snake(std::string texture, int xpos, int ypos, int size);
	~Snake();

	void OnRender() override;
	void OnKeyPressed() override;

	void Update(float elasedTime);

	bool IsAlive() { return alive; }
	int eatFood(Food& food);
	bool isContain(int x, int y);
private:
	
	
	struct point
	{
		int x;
		int y;
	};
	enum class Snake_Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	std::list<point> mBody;
	Snake_Direction mDirection;
	Snake_Direction mNextDirection;
	point mTail;
	int mSize;
	bool alive;
	int mScore;
	
	void die();
	void hitSelf();
	void changeDirection(Snake_Direction dir);

};