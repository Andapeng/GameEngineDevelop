#pragma once
#include "RenderableObject.h"
class Player : public RenderableObject
{
public:
	Player();
	Player(std::string texture, int xpos, int ypos, int xsize, int ysize);
	~Player();

	void OnKeyPressed() override;
	void Update(float elasedTime) override;
protected:
	
private:
	void MoveLeft(float deltatime);
	void MoveRight(float deltatime);
	void MoveUp(float deltatime);
	void MoveDown(float deltatime);

	

	enum class Player_State{
		AUTO,
		MANUAL
	};
	enum class Player_Direction {
		LEFT,
		RIGHT,
		UP, 
		DOWN
	};
	Player_State mState;
	Player_Direction mDirection;

	void ChangeState();
	void ChangeDirection(Player_Direction direction);

};