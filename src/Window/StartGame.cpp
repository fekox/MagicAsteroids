#include "raylib.h"
#include "Window/Game.h"
#include "Objects/PlayerShip.h"
#include "Window/StartGame.h"

Ship playerShip;

void StartGame()
{
    InitGame();
    
    GameLoop();
}

void InitGame()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");
    SetWindowState(FLAG_VSYNC_HINT);

    playerShip = CreateShip();

    playerShip.posX = screenWidth / 2;
    playerShip.posY = screenHeight / 2;
    playerShip.height = 100.0f;
    playerShip.widht = 50.0f;
    playerShip.speed = 500.0f;
    playerShip.lifes = 3;
    playerShip.points = 0;
    playerShip.rotation.x = 0;
    playerShip.rotation.y = 0;
}

void GameLoop() 
{
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        
        shipRotation();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        drawGame();

        EndDrawing();
    }

    CloseWindow();
}

void drawGame() 
{
    DrawShip(playerShip);
}

void shipRotation()
{

}

void shipMovement()
{

}