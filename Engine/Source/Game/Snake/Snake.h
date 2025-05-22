#pragma once
#include "../../Entities/RenderableObject.h"
#include <list>
#include "Food.h"
class Trap;

class Snake : public RenderableObject
{
public:
	Snake();
	Snake(std::string texture, int xpos, int ypos, int size);
	~Snake() override;

	void OnRender() override;
	void OnKeyPressed() override;
	bool IsCollide(std::shared_ptr<GameObject> gameObject) override;
	
	void Update(float elapsedTime) override;

	bool IsAlive() { return alive; }
	bool IsContain(int x, int y);
        void Reset();

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
	point mTail{0, 0};
	int mSize;
	bool alive;
	
	void die();
	void hitSelf();
        bool hitTrap(std::shared_ptr<Trap> trap);
	void changeDirection(Snake_Direction dir);
	int eatFood(Food& food);
};