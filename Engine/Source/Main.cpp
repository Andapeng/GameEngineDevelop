#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Application.h"
#include "Log.h"


int main(int argc, char** args) {
   Logger::LogInfo("Engine Start. ");
    //_CrtSetBreakAlloc(1887);
    Application app;
    app.Initialize();
    app.Run();
    app.Release();

    Logger::LogInfo("Engine end. ");

    _CrtDumpMemoryLeaks();
    return 0;
}