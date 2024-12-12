#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Application.h"
#include "Log.h"
#include "Game/Snake/SnakeGame.h"
#include "Game/Breakout/Breakout.h"


int main(int argc, char** args) {

	Logger::SetLogLevel("debug");
	Logger::LogInfo("Engine Start. ");
	//_CrtSetBreakAlloc(1887);
	Application app;
	// app.Initialize(new SnakeGame());
	app.Initialize(new Breakout);
	app.Run();
	app.Release();

	Logger::LogInfo("Engine end. ");

	_CrtDumpMemoryLeaks();
	return 0;
}
