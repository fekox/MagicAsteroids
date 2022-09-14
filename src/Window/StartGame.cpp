#include "raylib.h"
#include "Window/Game.h"

void StartGame()
{
    // Init
 //----------------------------------------------------------------------------------
    InitGame();
    
    GameLoop();
}

void InitGame()
{

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");
}

void GameLoop() 
{
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}