#include "Player.h"
#include "../Managers/InputManager.h"
extern InputManager* g_pInputManager;

static float Speed = 10.0f;

Player::Player()
	:RenderableObject(),
	mState(Player_State::MANUAL),
	mDirection(Player_Direction::RIGHT)
{
}

Player::Player(std::string texture, int xpos, int ypos, int xsize, int ysize)
	:RenderableObject(texture, xpos, ypos, xsize, ysize),
	mState(Player_State::MANUAL),
	mDirection(Player_Direction::RIGHT)
{
}

Player::~Player()
{
}

void Player::OnKeyPressed()
{
	if (mState == Player_State::AUTO)
	{
		if (g_pInputManager->IsKeyPressed("Left"))
		{
			mDirection = Player_Direction::LEFT;
		}
		if (g_pInputManager->IsKeyPressed("Right"))
		{
			mDirection = Player_Direction::RIGHT;
		}
		if (g_pInputManager->IsKeyPressed("Up"))
		{
			mDirection = Player_Direction::UP;
		}
		if (g_pInputManager->IsKeyPressed("Down"))
		{
			mDirection = Player_Direction::DOWN;
		}
	}
	else if (mState == Player_State::MANUAL)
	{
		if (g_pInputManager->IsKeyPressed("Left"))
		{
			this->MoveLeft(1);
		}
		if (g_pInputManager->IsKeyPressed("Right"))
		{
			this->MoveRight(1);
		}
		if (g_pInputManager->IsKeyPressed("Up"))
		{
			this->MoveUp(1);
		}
		if (g_pInputManager->IsKeyPressed("Down"))
		{
			this->MoveDown(1);
		}
	}

	if (g_pInputManager->IsKeyPressed("Space"))
	{
		ChangeState();
	}
	
}

void Player::Update(float elasedTime)
{
	if (mState == Player_State::AUTO)
	{
		if (mDirection == Player_Direction::LEFT)
		{
			this->MoveLeft(elasedTime);
		}
		if (mDirection == Player_Direction::RIGHT)
		{
			this->MoveRight(elasedTime);
		}
		if (mDirection == Player_Direction::UP)
		{
			this->MoveUp(elasedTime);
		}
		if (mDirection == Player_Direction::DOWN)
		{
			this->MoveDown(elasedTime);
		}
	}
}

void Player::MoveLeft(float deltatime)
{
	SetPosition(GetPosX() - Speed * deltatime, GetPosY(), 0);
}

void Player::MoveRight(float deltatime)
{
	SetPosition(GetPosX() + Speed * deltatime, GetPosY(), 0);
}

void Player::MoveUp(float deltatime)
{
	SetPosition(GetPosX(), GetPosY() - Speed * deltatime, 0);
}

void Player::MoveDown(float deltatime)
{
	SetPosition(GetPosX(), GetPosY() + Speed * deltatime, 0);
}

void Player::ChangeState()
{
	if (mState == Player_State::MANUAL)
	{
		mState = Player_State::AUTO;
		Speed = 100.0f;
	}
	else if (mState == Player_State::AUTO)
	{
		mState = Player_State::MANUAL;
		Speed = 10.0f;
	}
}

void Player::ChangeDirection(Player_Direction direction)
{
	mDirection = direction;
}
