#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Window/Game.h"
#include "Objects/PlayerShip.h"
#include "Objects/Asteroid.h"
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

//Asteroid
Asteroid asteroid;

//Window
int screenWidth = 1024;
int screenHeight = 768;

void StartGame()
{
    InitGame();
    
    GameLoop();
}

void InitGame()
{
    InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");
    SetWindowState(FLAG_VSYNC_HINT);

    //Player
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

    shipRec = GetRec(playerShip, playerShip.widht, playerShip.height);

    //Mouse
    mouse = CreateMouse();
    mouseRec = CreateRectangleMouse(mouse);

    //Asteroid
    asteroid.position.x = screenWidth / 4;
    asteroid.position.y = screenHeight / 4;

    asteroid.radius = 70.0f;
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
    DrawAsteroid(asteroid);
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

void shipTeleport(Vector2& shipPosition, int screenWidth, int screenHeight)
{
    if (shipPosition.x < 0)
    {
        shipPosition.x = shipPosition.x + screenWidth;
    }

    if (shipPosition.x >= screenWidth)
    {
        shipPosition.x = shipPosition.x - screenWidth;
    }

    if (shipPosition.y < 0)
    {
        shipPosition.y = shipPosition.y + screenHeight;
    }

    if (shipPosition.y >= screenHeight)
    {
        shipPosition.y = shipPosition.y - screenHeight;
    }
}