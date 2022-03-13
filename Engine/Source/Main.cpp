#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Application.h"

#include "Log.h"

using namespace std;

int main(int argc, char** args) {

    BOOST_LOG_TRIVIAL(info) << "Engine Start. ";

    //_CrtSetBreakAlloc(1887);
    Application app;
    app.Initialize();
    app.Run();
    app.Release();

    BOOST_LOG_TRIVIAL(info) << "Engine end. ";

    _CrtDumpMemoryLeaks();
    return 0;
}