#include "Snake.h"

#include <iostream>
#include <fmt/printf.h>
#include <string>
#include <format>

#include "../../Entities/Sprite.h"
#include "../../Managers/Managers.h"
#include "../../Renderer/SpriteRenderer.h"
#include "../../Renderer/TextRenderer.h"

#include "../../Config/GlobalConfiguration.h"
#include "../../Log.h"
#include "Wall.h"

static int tmp_game_width = DEFAULT_WIDTH;
static int tmp_game_height = DEFAULT_HEIGHT;

float Speed = 5.0f;
static float sTime = 0;

Snake::Snake()
	:RenderableObject(),
	mSize(0),
	mDirection(Snake_Direction::RIGHT),
	mNextDirection(Snake_Direction::RIGHT),
	alive(true)
{
}

Snake::Snake(std::string texture, int xpos, int ypos, int size)
	:RenderableObject(texture, xpos, ypos, size, size),
	mSize(size),
	mDirection(Snake_Direction::RIGHT),
	mNextDirection(Snake_Direction::RIGHT),
	alive(true)
{
	mBody.push_back({ xpos, ypos });
	mBody.push_back({ xpos+ size, ypos });
	mBody.push_back({ xpos+ size*2, ypos });

}

Snake::~Snake()
{
}

void Snake::OnRender()
{
	auto renderer = g_pGraphicsManager->GetSpriteRenderer();
	auto sprite = GetSprite();
	for (auto body : mBody)
	{
		renderer->RenderSprite(g_pResourceManager->GetTexture(sprite->GetTexture()), Eigen::Vector2f(body.x, body.y),
			Eigen::Vector2f(mSize, mSize), 0, Eigen::Vector3f(sprite->r(), sprite->g(), sprite->b()));
	}
}

void Snake::OnKeyPressed()
{
	
	if (g_pInputManager->IsKeyPressed("Right") && mDirection != Snake_Direction::LEFT)
	{
		mNextDirection = Snake_Direction::RIGHT;
	}
	else if (g_pInputManager->IsKeyPressed("Left") && mDirection != Snake_Direction::RIGHT)
	{
		mNextDirection = Snake_Direction::LEFT;
	}
	else if (g_pInputManager->IsKeyPressed("Up") && mDirection != Snake_Direction::DOWN)
	{
		mNextDirection = Snake_Direction::UP;
	}
	else if (g_pInputManager->IsKeyPressed("Down") && mDirection != Snake_Direction::UP)
	{
		mNextDirection = Snake_Direction::DOWN;
	}

}

bool Snake::IsCollide(GameObject* gameObject)
{
	Food* food = dynamic_cast<Food*>(gameObject);
	if (food != nullptr)
	{
		return this->eatFood(*food);
	}
	Wall* wall = dynamic_cast<Wall*>(gameObject);
	if (wall != nullptr)
	{
		die();
		return true;
	}
	return false;
}


void Snake::Update(float elasedTime)
{
	if (alive) 
	{
		sTime += elasedTime;
		if (sTime > 1.0f / Speed)
		{
			mTail = mBody.front();
			if (mNextDirection == Snake_Direction::RIGHT && mDirection != Snake_Direction::LEFT)
			{
				changeDirection(mNextDirection);
				mBody.pop_front();
				auto body = mBody.back();
				point newPoint = { body.x + mSize, body.y };
				if (newPoint.x >= tmp_game_width) newPoint.x = 0;
				mBody.push_back(newPoint);
			}
			if (mNextDirection == Snake_Direction::LEFT && mDirection != Snake_Direction::RIGHT)
			{
				changeDirection(mNextDirection);
				mBody.pop_front();
				auto body = mBody.back();
				point newPoint = { body.x - mSize, body.y };
				if (newPoint.x < 0) newPoint.x = tmp_game_width - mSize;
				mBody.push_back(newPoint);
			}
			if (mNextDirection == Snake_Direction::UP && mDirection != Snake_Direction::DOWN)
			{
				changeDirection(mNextDirection);
				mBody.pop_front();
				auto body = mBody.back();
				point newPoint = { body.x, body.y - mSize };
				if (newPoint.y < 0) newPoint.y = tmp_game_height - mSize;
				mBody.push_back(newPoint);
			}
			if (mNextDirection == Snake_Direction::DOWN && mDirection != Snake_Direction::UP)
			{
				changeDirection(mNextDirection);
				mBody.pop_front();
				auto body = mBody.back();
				point newPoint = { body.x, body.y + mSize };
				if (newPoint.y >= tmp_game_height) newPoint.y = 0;
				mBody.push_back(newPoint);
			}
			hitSelf();
			sTime = 0;
		}
	}
}

int Snake::eatFood(Food& food)
{
	auto foodPosX = food.GetPosX();
	auto foodPosY = food.GetPosY();

	auto body = mBody.back();

	if (foodPosX == body.x && foodPosY == body.y) {

		Logger::LogInfo(fmt::format("snake eat food {1} : {0} ", foodPosX, foodPosY));
		mBody.push_front(mTail);
		food.Produce(this);
		return 1;
	}
	return 0;
}

bool Snake::IsContain(int x, int y)
{
	int num = 0;
	for (auto body : mBody)
	{
		if (x == body.x && y == body.y && num != mBody.size())
		{
			Logger::LogInfo("x, y is a snake body");
			return true;
		}
		num++;
	}
	return false;
	
}

void Snake::die()
{
	alive = false;
}

void Snake::hitSelf()
{
	int num = 0;
	auto head = mBody.back();
	for (auto body : mBody)
	{
		if (head.x == body.x && head.y == body.y && num != mBody.size() - 1)
		{
			alive = false;
			Logger::LogInfo("hit snake self");
		}
		num++;
	}
}

void Snake::changeDirection(Snake_Direction dir)
{
	mDirection = dir;
}
