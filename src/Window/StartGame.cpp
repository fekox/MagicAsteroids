#include "raylib.h"
#include "Window/Game.h"
#include "Objects/PlayerShip.h"
#include "Objects/Mouse.h"
#include "Window/StartGame.h"

Ship playerShip;

Mouse mouse;

Rectangle rec;

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

    playerShip.position.x = screenWidth / 2;
    playerShip.position.y = screenHeight / 2;
    playerShip.height = 100.0f;
    playerShip.widht = 50.0f;
    playerShip.speed = 500.0f;
    playerShip.lifes = 3;
    playerShip.points = 0;

    mouse = CreateMouse();

    rec = CreateRectangle(mouse);
}

void GameLoop() 
{
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        HideCursor();
        mouse.position = GetMousePosition();
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
    DrawMouse(mouse, rec);
    
}

void shipRotation()
{
    GetShipPosition(playerShip.position);
}

void shipMovement()
{

}