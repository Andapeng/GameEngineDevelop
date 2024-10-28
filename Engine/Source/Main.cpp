#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Application.h"
#include "Log.h"
#include "Game/Snake/SnakeGame.h"


int main(int argc, char** args) {
   Logger::LogInfo("Engine Start. ");
    //_CrtSetBreakAlloc(1887);
    Application app;
    app.Initialize(new SnakeGame());
    app.Run();
    app.Release();

    Logger::LogInfo("Engine end. ");

    _CrtDumpMemoryLeaks();
    return 0;
}
