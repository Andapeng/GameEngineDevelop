#pragma once
#include "Entities/RenderableObject.h"
#include <list>
#include "Food.h"
class Snake : public RenderableObject
{
public:
	Snake();
	Snake(std::string texture, int xpos, int ypos, int size);
	~Snake() override;

	void OnRender() override;
	void OnKeyPressed() override;
	bool IsCollide(GameObject* gameObject) override;
	void Update(float elasedTime) override;

	bool IsAlive() { return alive; }
	bool IsContain(int x, int y);
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
	
	void die();
	void hitSelf();
	void changeDirection(Snake_Direction dir);
	int eatFood(Food& food);
};