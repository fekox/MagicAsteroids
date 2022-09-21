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

    playerShip.height = 60.0f;
    playerShip.widht = 60.0f;

    playerShip.speed = 100.0f;
    playerShip.lifes = 3;
    playerShip.points = 0;

    shipRec = GetRec(playerShip, playerShip.widht, playerShip.height);

    //Mouse
    mouse = CreateMouse();

    mouse.position.x = 0;
    mouse.position.y = 0;

    mouse.width = 20.0f;
    mouse.height = 20.0f;

    mouseRec = GetRecMouse(mouse, mouse.width, mouse.height);

    //Asteroid
    asteroid.position.x = 100.0f;
    asteroid.position.y = 100.0f;

    asteroid.radius = 80.0f;
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
        AsteroidCollision(playerShip, asteroid, asteroid.radius);

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

bool CheckCollisionCirRec(Vector2 asteroidPos, float asteroidRadius, Rectangle rect)
{
    Vector2 perimeter;

    perimeter.x = asteroidPos.x;

    if (perimeter.x < rect.x)
    {
        perimeter.x = rect.x;
    }

    if (perimeter.x > rect.x + rect.width)
    {
        perimeter.x = rect.x + rect.width;
    }

    perimeter.y = asteroidPos.y;

    if (perimeter.y < rect.y)
    {
        perimeter.y = rect.y;
    }

    if (perimeter.y > rect.y + rect.height)
    {
        perimeter.y = rect.y + rect.height;
    }

    float distance = sqrt((asteroidPos.x - perimeter.x) * (asteroidPos.x - perimeter.x) + (asteroidPos.y - perimeter.y) * (asteroidPos.y - perimeter.y));

    if (distance <= asteroidRadius) 
    {
        return true;
    }

    return false;
}

void AsteroidCollision(Ship& playerShip, Asteroid& asteroid, float radius)
{
    if (CheckCollisionCirRec(Vector2{asteroid.position.x + 35, asteroid.position.y + 30}, radius - 15, GetRec(playerShip, playerShip.widht, playerShip.height)))
    {

        cout << "colision" << endl;
        
    }
}