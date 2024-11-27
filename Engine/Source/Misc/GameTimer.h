#pragma once
#include <SFML/System/Clock.hpp>
#include <memory>
class GameTimer
{
public:
	float Start();
	float Pause();
	float GetElapsedTime();

private:
	float mElapsedTime = 0.0f;
	float mCurrentTime = 0.0f;
	float mPausedTime = 0.0f;
	std::unique_ptr<sf::Clock> mClock;

	bool mStopped = true;
};
