#include <cmath>
#include "raylib.h"
#include "Window/Game.h"
#include "Objects/PlayerShip.h"
#include "Objects/Mouse.h"
#include "Window/StartGame.h"

//Player
Ship playerShip;
Vector2 shipDirection;
Vector2 shipDirNormalize;

//Mouse
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

    shipDirection.x = 100;
    shipDirection.y = 100;

    playerShip.position.x = screenWidth / 2;
    playerShip.position.y = screenHeight / 2;

    playerShip.direction.x = 0;
    playerShip.direction.y = 0;

    playerShip.angle = 0;

    playerShip.height = 50.0f;
    playerShip.widht = 100.0f;

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
        mouseMovement();
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
    shipMovement();
}

void mouseMovement()
{
    mouse.position = GetMousePosition();
}

void shipMovement()
{
    shipDirection.x = mouse.position.x - playerShip.position.x;
    shipDirection.y = mouse.position.y - playerShip.position.y;

    playerShip.angle = atan(shipDirection.y / shipDirection.x);

    playerShip.rotation = playerShip.angle;

    //shipDirNormalize.x = shipDirection.x / Vector2Lenght(shipDirection);

    //playerShip.position.x = shipDirection.x * GetFrameTime();
    //playerShip.position.y = shipDirection.y * GetFrameTime();

}