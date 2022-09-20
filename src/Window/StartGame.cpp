#include <iostream>
#include <cmath>
#include "raylib.h"
#include "Window/Game.h"
#include "Objects/PlayerShip.h"
#include "Objects/Mouse.h"
#include "Window/StartGame.h"

using namespace std;

//Player
Ship playerShip;
Vector2 shipDirNormalize;
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

    playerShip.directionX = 0;
    playerShip.directionY = 0;

    playerShip.angle = 0;

    playerShip.height = 60.0f;
    playerShip.widht = 30.0f;

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
    //shipActualPos.x = playerShip.position.x;
    //shipActualPos.y = playerShip.position.y;

    //playerShip.directionX = mouse.position.x - shipActualPos.x;
    //playerShip.directionY = mouse.position.y - shipActualPos.y;

    //playerShip.angle = atan(playerShip.directionY / playerShip.directionX);

    //playerShip.rotation = playerShip.angle;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        playerShip.directionX += sin(playerShip.angle) * playerShip.speed * GetFrameTime();
        playerShip.directionY += -cos(playerShip.angle) * playerShip.speed * GetFrameTime();
    }

    playerShip.position.x += playerShip.directionX * GetFrameTime();
    playerShip.position.y += playerShip.directionY * GetFrameTime();

    shipTeleport(playerShip.position, screenWidth, screenHeight);
}