#include "GameTimer.h"

float GameTimer::Start()
{
	mStopped = false;
	mClock = std::make_unique<sf::Clock>();
	return mCurrentTime;
}

float GameTimer::Pause()
{
	mPausedTime = mClock->getElapsedTime().asSeconds();
	mStopped = true;
	return mPausedTime;
}


float GameTimer::GetElapsedTime()
{
	mElapsedTime = mClock->restart().asSeconds();
	return mElapsedTime;
}
