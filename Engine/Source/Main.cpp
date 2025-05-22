#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Application.h"
#include "Game/Snake/SnakeGame.h"
#include "Game/Breakout/Breakout.h"
#include "Log.h"
#include "Game/Tetris/TetrisGame.h"


int main(int argc, char** args) {

    Logger::Initialize();
    Logger::SetLogLevel("Debug");
    Logger::LogInfo("Engine Start. ");
    //_CrtSetBreakAlloc(1887);
    Application app;
    // app.Initialize(std::make_shared<SnakeGame>());
    // app.Initialize(std::make_shared<Breakout>());
    app.Initialize(std::make_shared<TetrisGame>());
    app.Run();
    app.Release();

    Logger::LogInfo("Engine end. ");

    _CrtDumpMemoryLeaks();
    return 0;
}
