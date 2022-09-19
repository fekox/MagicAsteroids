#include "raylib.h"
#include "Window/Game.h"
#include "Objects/PlayerShip.h"

Ship playerShip;

void StartGame()
{
    InitGame();
    
    GameLoop();
}

void InitGame()
{

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");
    SetWindowState(FLAG_VSYNC_HINT);

    playerShip = CreateShip();

    playerShip.posX = GetScreenWidth() / 2;
    playerShip.posY = GetScreenWidth() / 2;
    playerShip.height = 40.0f;
    playerShip.widht = 40.0f;
    playerShip.speed = 500.0f;
    playerShip.lifes = 3;
    playerShip.points = 0;
    playerShip.rotation = 0;
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