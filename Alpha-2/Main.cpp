#include "raylib.h"
#include "Game.h"
#include "GlobalConsts.h"

#include <iostream>

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Alpha-2");
    SetTargetFPS(60);  

    GameInitialize();

    while (!WindowShouldClose()) {  
        GameUpdate();
        GameDraw();
    }

    GameClose();
    CloseWindow();  
    return 0;
}