#include "Snake.h"
#include <string>
#include <format>

#include "../../Entities/Sprite.h"
#include "../../Managers/Managers.h"
#include "../../Renderer/SpriteRenderer.h"

#include "../../Config/GlobalConfiguration.h"
#include "../../Log.h"
#include "Trap.h"

static int tmp_game_width = DEFAULT_WIDTH;
static int tmp_game_height = DEFAULT_HEIGHT;

float Speed = 5.0f;
static float sTime = 0;

Snake::Snake()
	:RenderableObject(),
	mDirection(Snake_Direction::RIGHT),
	mNextDirection(Snake_Direction::RIGHT),
	mSize(0),
	alive(true)
{
}

Snake::Snake(std::string texture, int xpos, int ypos, int size)
  : RenderableObject(texture, xpos, ypos, size, size)
  , mDirection(Snake_Direction::RIGHT)
  , mNextDirection(Snake_Direction::RIGHT)
  , mSize(size)
  , alive(true)
{
    mBody.push_back({ xpos, ypos });
    mBody.push_back({ xpos + size, ypos });
    mBody.push_back({ xpos + size * 2, ypos });
}

Snake::~Snake()
{
}

void
Snake::OnRender()
{
    auto renderer = g_pGraphicsManager->GetSpriteRenderer();
    auto sprite = GetSprite();
    for (auto body : mBody) {
        renderer->AddSprite(std::make_shared<Sprite>(sprite->GetTexture(),
                                                     body.x,
                                                     body.y,
                                                     0.0f,
                                                     mSize,
                                                     mSize,
                                                     sprite->r(),
                                                     sprite->g(),
                                                     sprite->b()));
    }
}

void
Snake::OnKeyPressed()
{

    if (g_pInputManager->IsKeyPressed("Right") &&
        mDirection != Snake_Direction::LEFT) {
        mNextDirection = Snake_Direction::RIGHT;
    } else if (g_pInputManager->IsKeyPressed("Left") &&
               mDirection != Snake_Direction::RIGHT) {
        mNextDirection = Snake_Direction::LEFT;
    } else if (g_pInputManager->IsKeyPressed("Up") &&
               mDirection != Snake_Direction::DOWN) {
        mNextDirection = Snake_Direction::UP;
    } else if (g_pInputManager->IsKeyPressed("Down") &&
               mDirection != Snake_Direction::UP) {
        mNextDirection = Snake_Direction::DOWN;
    }
}

bool Snake::IsCollide(std::shared_ptr<GameObject> gameObject)
{
    auto food = dynamic_pointer_cast<Food>(gameObject);
    if (food != nullptr) {
        return this->eatFood(*food);
    }
    auto trap = dynamic_pointer_cast<Trap>(gameObject);
    if (trap != nullptr) {
        return hitTrap(trap);
    }
    return false;
}


void
Snake::Update(float elapsedTime)
{
    if (alive) {
        sTime += elapsedTime;
        if (sTime > 1.0f / Speed) {
            mTail = mBody.front();
            if (mNextDirection == Snake_Direction::RIGHT &&
                mDirection != Snake_Direction::LEFT) {
                changeDirection(mNextDirection);
                mBody.pop_front();
                auto body = mBody.back();
                point newPoint = { body.x + mSize, body.y };
                if (newPoint.x >= tmp_game_width)
                    newPoint.x = 0;
                mBody.push_back(newPoint);
            }
            if (mNextDirection == Snake_Direction::LEFT &&
                mDirection != Snake_Direction::RIGHT) {
                changeDirection(mNextDirection);
                mBody.pop_front();
                auto body = mBody.back();
                point newPoint = { body.x - mSize, body.y };
                if (newPoint.x < 0)
                    newPoint.x = tmp_game_width - mSize;
                mBody.push_back(newPoint);
            }
            if (mNextDirection == Snake_Direction::UP &&
                mDirection != Snake_Direction::DOWN) {
                changeDirection(mNextDirection);
                mBody.pop_front();
                auto body = mBody.back();
                point newPoint = { body.x, body.y - mSize };
                if (newPoint.y < 0)
                    newPoint.y = tmp_game_height - mSize;
                mBody.push_back(newPoint);
            }
            if (mNextDirection == Snake_Direction::DOWN &&
                mDirection != Snake_Direction::UP) {
                changeDirection(mNextDirection);
                mBody.pop_front();
                auto body = mBody.back();
                point newPoint = { body.x, body.y + mSize };
                if (newPoint.y >= tmp_game_height)
                    newPoint.y = 0;
                mBody.push_back(newPoint);
            }
            hitSelf();
            sTime = 0;
        }
    }
}

int
Snake::eatFood(Food& food)
{
    auto foodPosX = static_cast<int>(food.GetPosX());
    auto foodPosY = static_cast<int>(food.GetPosY());

    auto body = mBody.back();

    if (foodPosX == body.x && foodPosY == body.y) {

        Logger::LogInfo(
          std::format("snake eat food {1} : {0} ", foodPosX, foodPosY));
        mBody.push_front(mTail);
        food.Produce(this);
        return 1;
    }
    return 0;
}

bool
Snake::IsContain(int x, int y)
{
    int num = 0;
    for (auto body : mBody) {
        if (x == body.x && y == body.y && num != mBody.size()) {
            Logger::LogInfo("x, y is a snake body");
            return true;
        }
        num++;
    }
    return false;
}

void Snake::Reset()
{
    mBody.clear();
    mBody.push_back({ 0, 0 });
    mBody.push_back({ mSize, 0 });
    mBody.push_back({ mSize * 2, 0 });
    alive = true;
    mDirection = Snake_Direction::RIGHT;
    mNextDirection = Snake_Direction::RIGHT;
}

void
Snake::die()
{
    alive = false;
}

void
Snake::hitSelf()
{
    int num = 0;
    auto head = mBody.back();
    for (auto body : mBody) {
        if (head.x == body.x && head.y == body.y && num != mBody.size() - 1) {
            alive = false;
            Logger::LogInfo("hit snake self");
        }
        num++;
    }
}

bool Snake::hitTrap(std::shared_ptr<Trap> trap)
{
    auto trapPosX = static_cast<int>(trap->GetPosX());
    auto trapPosY = static_cast<int>(trap->GetPosY());

    auto body = mBody.back();

    if (trapPosX == body.x && trapPosY == body.y) {
        Logger::LogInfo(
          std::format("snake hit trap {1} : {0} ", trapPosX, trapPosY));
        alive = false;
    }
    return !alive;
}

void
Snake::changeDirection(Snake_Direction dir)
{
    mDirection = dir;
}
