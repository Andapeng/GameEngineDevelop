#include <iostream>
#include "Game/RpgGame.h"

using namespace std;

int main(int argc, char** args) {
    RpgGame game;
    game.Initialize();
    game.Tick();
    game.Release();
    
    return 0;
}