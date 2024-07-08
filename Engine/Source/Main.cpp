#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Application.h"
#include "Log.h"

#define RUN_TEST_CASE 1

#ifdef RUN_TEST_CASE
#include <gtest/gtest.h>
#endif

int main(int argc, char** args) {

#ifdef RUN_TEST_CASE
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
#endif

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