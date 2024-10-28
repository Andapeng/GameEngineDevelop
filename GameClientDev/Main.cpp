#include <iostream>

#include "Application.h"
#include "Game/Snake/Source/SnakeGameInstance.h"
#include "math/Math.h"

int main()
{

	std::cout << "hello world!" << std::endl;

    Application app;
    app.Initialize(new SnakeGameInstance());
    app.Run();
    app.Release();
}
