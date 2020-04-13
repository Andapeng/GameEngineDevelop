#include "Snake.h"

#include "../../Entities/Sprite.h"
#include "../../Managers/Managers.h"
#include "../../Renderer/SpriteRenderer.h"
#include "../../Renderer/TextRenderer.h"

#include "../GlobalConfiguration.h"

#include <iostream>
#include <fmt/printf.h>
#include <string>

static int tmp_game_width = DEFAULT_WIDTH;
static int tmp_game_height = DEFAULT_HEIGHT;

float Speed = 5.0f;
static float time = 0;

std::wstring text = L"µÃ·Ö£º";

Snake::Snake()
	:RenderableObject(),
	mSize(0),
	mDirection(Snake_Direction::RIGHT),
	mNextDirection(Snake_Direction::RIGHT),
	alive(true),
	mScore(0)
{
}

Snake::Snake(std::string texture, int xpos, int ypos, int size)
	:RenderableObject(texture, xpos, ypos, size, size),
	mSize(size),
	mDirection(Snake_Direction::RIGHT),
	mNextDirection(Snake_Direction::RIGHT),
	alive(true),
	mScore(0)
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
	auto textRenderer = g_pGraphicsManager->GetTextRenderer();
	auto sprite = GetSprite();
	for (auto body : mBody)
	{
		renderer->RenderSprite(g_pResourceManager->GetTexture(sprite->GetTexture()), Eigen::Vector2f(body.x, body.y),
			Eigen::Vector2f(mSize, mSize), 0, Eigen::Vector3f(sprite->r(), sprite->g(), sprite->b()));
	}
	textRenderer->RenderText(text+ std::to_wstring(mScore), 0.0f, 10.0f, 1.0f, Eigen::Vector3f(1.0f, 0.0f, 0.0f));
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

void Snake::Update(float elasedTime)
{
	if (alive) 
	{
		time += elasedTime;
		if (time > 1.0f / Speed)
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
			time = 0;
		}
	}
}

int Snake::eatFood(Food& food)
{
	auto foodPosX = food.GetPosX();
	auto foodPosY = food.GetPosY();

	auto body = mBody.back();

	if (foodPosX == body.x && foodPosY == body.y) {

		//std::cout << "snake eat food " << foodPosX << " : " << foodPosY << std::endl;
		fmt::print("snake eat food {1} : {0} ", foodPosX, foodPosY);
		mBody.push_front(mTail);
		food.Produce(this);
		mScore += 50;
		std::cout << "total score: " << mScore << std::endl;
		return 1;
	}
	return 0;
}

bool Snake::isContain(int x, int y)
{
	int num = 0;
	for (auto body : mBody)
	{
		if (x == body.x && y == body.y && num != mBody.size())
		{
			std::cout << "x, y is a snake body" << std::endl;
			return true;
		}
		num++;
	}
	return false;
	
}

void Snake::die()
{
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
			std::cout << "hit snake self" << std::endl;
		}
		num++;
	}
}

void Snake::changeDirection(Snake_Direction dir)
{
	mDirection = dir;
}
