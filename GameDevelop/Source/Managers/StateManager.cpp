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

void StateManager::GameStart()
{
	mGameState = GameState::running;
}

void StateManager::GameClose()
{
	mGameState = GameState::closed;
}

bool StateManager::IsGameRuning()
{
	if (mGameState == GameState::running)
	{
		return true;
	}
	return false;
}
