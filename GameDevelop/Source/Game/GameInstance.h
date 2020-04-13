#pragma once
class GameInstance
{
public:
	virtual int Initialize();
	virtual int Tick();
	virtual int Release();

	// manage event
	virtual void ProcessInput();

	// manage render
	virtual void Render();

	// game state update
	virtual void Update(float elapsedTime);

	// manage physics
	virtual void DetectCollide();

	virtual int Start();
	virtual int Pause();
	virtual int Stop();
private:

};