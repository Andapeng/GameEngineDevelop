#include "StateManager.h"

StateManager* StateManager::mSingleStateMgr = nullptr;

StateManager::StateManager()
	:m_gameState(GameState::closed)
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
	m_gameState = GameState::running;
}

void StateManager::GameOver()
{
	m_gameState = GameState::closed;
}

void StateManager::GamePause()
{
	m_gameState = GameState::paused;
}

bool StateManager::IsGameRunning()
{
	return m_gameState == GameState::running;
}

bool StateManager::IsGameOver()
{
	return m_gameState == GameState::closed;
}

bool StateManager::IsGamePause()
{
	return m_gameState == GameState::paused;

}
