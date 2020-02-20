#pragma once
class StateManager
{
private:
	static StateManager* mSingleStateMgr;
public:

	
	static StateManager* Get();
	void GameStart();
	void GameClose();

	bool IsGameRuning();
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