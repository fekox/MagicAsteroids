#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Window/Game.h"
#include "Window/StartGame.h"
#include "Objects/PlayerShip.h"
#include "Objects/Asteroid.h"
#include "Objects/Mouse.h"

using namespace std;

//Player
Ship playerShip;
Rectangle shipRec;
Vector2 shipOriginRec;

//Mouse
Mouse mouse;
Rectangle mouseRec;

//Asteroid
Asteroid asteroid;

//Window
Texture2D background;
int screenWidth = 1024;
int screenHeight = 768;

void StartGame()
{
    InitGame();
    
    GameLoop();
}

void InitGame()
{
    //Window
    InitWindow(screenWidth, screenHeight, "Asteroids_FacundoSantos");
    SetWindowState(FLAG_VSYNC_HINT);

    background = LoadTexture("resources/Background.png");

    //Player
    playerShip = CreateShip();
    shipRec = GetRec(playerShip, playerShip.widht, playerShip.height);
    shipOriginRec.x = shipRec.width / 2;
    shipOriginRec.y = shipRec.height / 2;

    //Mouse
    mouse = CreateMouse();
    mouseRec = GetRecMouse(mouse, mouse.width, mouse.height);

    //Asteroid
    asteroid = CreateAsteroid();
}

void GameLoop() 
{
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------

        HideCursor();
        asteroidMovement();
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

    UnloadTexture(playerShip.texture);
    UnloadTexture(asteroid.texture);
    UnloadTexture(mouse.texture);
    UnloadTexture(background);
    CloseWindow();
}

void drawGame() 
{
    DrawTexture(background, 0, 0, WHITE);
    DrawShip(playerShip, shipOriginRec);
    DrawAsteroid(asteroid);
    DrawMouse(mouse, mouseRec);
}

void mouseMovement()
{
    mouse.position = GetMousePosition();
}

void shipMovement()
{
    Vector2 distanceDiff;
    Vector2 shipActualPos;

    playerShip.source = { 0,0, (float)playerShip.texture.width, (float)playerShip.texture.height };
    playerShip.dest = { playerShip.position.x, playerShip.position.y, playerShip.widht, playerShip.height };

    shipActualPos.x = playerShip.position.x;
    shipActualPos.y = playerShip.position.y;

    distanceDiff.x = mouse.position.x - shipActualPos.x;
    distanceDiff.y = mouse.position.y - shipActualPos.y;

    float angle = atan(distanceDiff.y / distanceDiff.x);
    angle = angle * 180 / PI;

    if (distanceDiff.x < 0)
    {
        angle += 180;
    }

    playerShip.rotation = angle;


    Vector2 shipDirNormalize;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        shipDirNormalize = Vector2Normalize(distanceDiff);

        playerShip.aceleration.x += shipDirNormalize.x;
        playerShip.aceleration.y += shipDirNormalize.y;
    }

    playerShip.position.x = playerShip.position.x + playerShip.aceleration.x * GetFrameTime();
    playerShip.position.y = playerShip.position.y + playerShip.aceleration.y * GetFrameTime();

    objTeleport(playerShip.position, screenWidth, screenHeight);
}

void asteroidMovement()
{
    asteroid.position.x += asteroid.speed * GetFrameTime();
    asteroid.position.y += asteroid.speed * GetFrameTime();

    objTeleport(asteroid.position, screenWidth, screenHeight);
}

void objTeleport(Vector2& objPosition, int screenWidth, int screenHeight)
{
    if (objPosition.x < 0)
    {
        objPosition.x = objPosition.x + screenWidth;
    }

    if (objPosition.x >= screenWidth)
    {
        objPosition.x = objPosition.x - screenWidth;
    }

    if (objPosition.y < 0)
    {
        objPosition.y = objPosition.y + screenHeight;
    }

    if (objPosition.y >= screenHeight)
    {
        objPosition.y = objPosition.y - screenHeight;
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