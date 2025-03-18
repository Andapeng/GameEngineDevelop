#include "StateManager.h"

StateManager* StateManager::mSingleStateMgr = nullptr;

StateManager::StateManager()
	:mGameState(GameState::closed)
{

}

StateManager* StateManager::Get()
{
	if (mSingleStateMgr == nullptr)
	{
		mSingleStateMgr = new StateManager;
	}
	return mSingleStateMgr;
}

void StateManager::Release()
{
	delete mSingleStateMgr;
}

void StateManager::GameStart()
{
	mGameState = GameState::running;
}

void StateManager::GameOver()
{
	mGameState = GameState::closed;
}

void StateManager::GamePause()
{
	mGameState = GameState::paused;
}

bool StateManager::IsGameRunning()
{
	return mGameState == GameState::running;
}

bool StateManager::IsGameOver()
{
	return mGameState == GameState::closed;
}

bool StateManager::IsGamePause()
{
	return mGameState == GameState::paused;

}
