#pragma once
class StateManager
{
private:
	static StateManager* mSingleStateMgr;
public:

	
	static StateManager* Get();

	void Release();

	void GameStart();
	void GameOver();
	void GamePause();

	bool IsGameRunning();
	bool IsGameOver();
	bool IsGamePause();
private:

	enum class GameState
	{
		running = 0,
		closed = 1,
		paused = 2,
		menu = 3
	};
	GameState m_gameState;
	

private:
	StateManager();
};

extern StateManager* g_pStateManager;