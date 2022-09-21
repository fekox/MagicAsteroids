#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Window/Game.h"
#include "Objects/PlayerShip.h"
#include "Objects/Mouse.h"
#include "Window/StartGame.h"

using namespace std;

//Player
Ship playerShip;
Vector2 shipActualPos;
Rectangle shipRec;

//Mouse
Mouse mouse;
Rectangle mouseRec;

int screenWidth = 1920;
int screenHeight = 1080;

void StartGame()
{
    InitGame();
    
    GameLoop();
}

void InitGame()
{
    InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");
    SetWindowState(FLAG_VSYNC_HINT);

    playerShip = CreateShip();

    playerShip.position.x = screenWidth / 2;
    playerShip.position.y = screenHeight / 2;

    playerShip.direction.x = 0;
    playerShip.direction.y = 0;

    playerShip.aceleration.x = 100.0f;
    playerShip.aceleration.y = 100.0f;

    playerShip.angle = 0;

    playerShip.height = 30.0f;
    playerShip.widht = 60.0f;

    playerShip.speed = 100.0f;
    playerShip.lifes = 3;
    playerShip.points = 0;

    shipRec = CreateRectangleShip(playerShip);

    mouse = CreateMouse();

    mouseRec = CreateRectangleMouse(mouse);
}

void GameLoop() 
{
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        HideCursor();
        mouseMovement();
        shipMovement();     

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
    DrawShip(playerShip, shipRec);
    DrawMouse(mouse, mouseRec);   
}

void mouseMovement()
{
    mouse.position = GetMousePosition();
}

void shipMovement()
{
    Vector2 distanceDiff;

    shipActualPos.x = playerShip.position.x;
    shipActualPos.y = playerShip.position.y;

    distanceDiff.x = mouse.position.x - shipActualPos.x;
    distanceDiff.y = mouse.position.y - shipActualPos.y;

    playerShip.angle = atan(distanceDiff.y / distanceDiff.x);
    playerShip.angle = playerShip.angle * 180 / PI;

    playerShip.rotation = playerShip.angle;

    Vector2 shipDirNormalize;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        shipDirNormalize = Vector2Normalize(distanceDiff);

        playerShip.aceleration.x += shipDirNormalize.x;
        playerShip.aceleration.y += shipDirNormalize.y;
    }

    playerShip.position.x= playerShip.position.x + playerShip.aceleration.x * GetFrameTime();
    playerShip.position.y = playerShip.position.y + playerShip.aceleration.y * GetFrameTime();

    shipTeleport(playerShip.position, screenWidth, screenHeight);
}