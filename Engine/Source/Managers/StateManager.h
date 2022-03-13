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

	bool IsGameRuning();
	bool IsGameOver();
private:

	enum class GameState
	{
		running = 0,
		closed = 1,
		paused = 2
	};
	GameState mGameState;
	

private:
	StateManager();
};

extern StateManager* g_pStateManager;