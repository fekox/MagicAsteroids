#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Window/Game.h"
#include "Window/StartGame.h"
#include "Objects/PlayerShip.h"
#include "Objects/Asteroid.h"
#include "Objects/Mouse.h"
#include "Objects/Bullet.h"

using namespace std;

//Player
Ship playerShip;
Rectangle shipRec;
Vector2 shipOriginRec;
Vector2 shipDirNormalize;

//Bullet
const int maxBullets = 10;
Bullet bullet[maxBullets];

//Mouse
Mouse mouse;
Rectangle mouseRec;

//Asteroid
const int maxAteroids = 5;
Asteroid asteroid[maxAteroids];

const int maxNormalAsteroid = 10;
Asteroid asteroidNor[maxNormalAsteroid];

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
    HideCursor();
    mouse = CreateMouse();
    mouseRec = GetRecMouse(mouse, mouse.width, mouse.height);

    //Asteroid
    for (int i = 0; i < maxAteroids; i++)
    {
        asteroid[i] = CreateAsteroid();
    }

    for (int i = 0; i < maxNormalAsteroid; i++)
    {
        asteroidNor[i] = CreateAsteroid();
        asteroidNor[i].radius = 45;
    }

    //Bullet
    for (int i = 0; i < maxBullets; i++)
    {
        bullet[i] = CreateBullet();
    }
}

void GameLoop() 
{
    while (!WindowShouldClose())
    {
        Input();
        Update();
        Collision();
        Draw();
    }

    UnloadData();
    CloseWindow();
}

void Input()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        shipDirNormalize = Vector2Normalize(playerShip.direction);

        playerShip.aceleration.x += shipDirNormalize.x;
        playerShip.aceleration.y += shipDirNormalize.y;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        for (int i = 0; i < maxBullets; i++)
        {
            if (bullet[i].isActive == false)
            {
                if (!bullet[i].isMoving)
                {
                    bullet[i].isActive = true;
                    bullet[i].isMoving = true;

                    bullet[i].direction.x = mouse.position.x - bullet[i].position.x;
                    bullet[i].direction.y = mouse.position.y - bullet[i].position.y;

                    bullet[i].direction = Vector2Normalize(bullet[i].direction);

                    break;
                }
            }
        }
    }
}

void Update()
{
    shipMovement();
    asteroidMovement();
    bulletMovement();
    mouseMovement();
}

void Collision()
{
    AsteroidCollision(playerShip);

    for (int i = 0; i < maxAteroids; i++)
    {
        BulletCollision(asteroid[i]);

        objCollisionLimit(asteroid[i].position, screenWidth, screenHeight);
    }

    objCollisionLimit(playerShip.position, screenWidth, screenHeight);

    bulletCollisonLimit();
    
}

void Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    drawGame();
    EndDrawing();
}

void drawGame() 
{
    DrawTexture(background, 0, 0, WHITE);    
    
    for (int i = 0; i < maxBullets; i++)
    {
        DrawBullet(bullet[i]);
    }

    DrawShip(playerShip, shipOriginRec, playerShip.widht, playerShip.height);
    
    for (int i = 0; i < maxAteroids; i++)
    {
        DrawAsteroid(asteroid[i]);
    }
    DrawMouse(mouse, mouseRec);
}

void mouseMovement()
{
    mouse.position = GetMousePosition();
}

void shipMovement()
{
    Vector2 shipActualPos;

    playerShip.source = { 0,0, (float)playerShip.texture.width, (float)playerShip.texture.height };
    playerShip.dest = { playerShip.position.x, playerShip.position.y, playerShip.widht, playerShip.height };

    shipActualPos.x = playerShip.position.x;
    shipActualPos.y = playerShip.position.y;

    playerShip.direction.x = mouse.position.x - shipActualPos.x;
    playerShip.direction.y = mouse.position.y - shipActualPos.y;

    float angle = atan(playerShip.direction.y / playerShip.direction.x);
    angle = angle * 180 / PI;

    if (playerShip.direction.x < 0)
    {
        angle += 180;
    }

    playerShip.rotation = angle;

    playerShip.position.x = playerShip.position.x + playerShip.aceleration.x * GetFrameTime();
    playerShip.position.y = playerShip.position.y + playerShip.aceleration.y * GetFrameTime();
}

void asteroidMovement()
{
    for (int i = 0; i < maxAteroids; i++)
    {
        if (asteroid[i].speed.x != 0 && asteroid[i].speed.y != 0)
        {
            asteroid[i].position.x += asteroid[i].speed.x * GetFrameTime();
            asteroid[i].position.y += asteroid[i].speed.y * GetFrameTime();
        }

        else
        {
            asteroid[i].speed.x = GetRandomValue(-70, 70);
            asteroid[i].speed.y = GetRandomValue(-70, 70);

            asteroid[i].position.x += asteroid[i].speed.x * GetFrameTime();
            asteroid[i].position.y += asteroid[i].speed.y * GetFrameTime();
        }

    }
}

void bulletMovement()
{
    for (int i = 0; i < maxBullets; i++)
    {
        if (bullet[i].isMoving == false)
        {
            bullet[i].position.x = playerShip.position.x - playerShip.widht / 2;
            bullet[i].position.y = playerShip.position.y - playerShip.height / 2;
        }

        if (bullet[i].isMoving)
        {
            bullet[i].position.x += bullet[i].direction.x * bullet[i].speed * GetFrameTime();
            bullet[i].position.y += bullet[i].direction.y * bullet[i].speed * GetFrameTime();
        }
    }    
}

void objCollisionLimit(Vector2& objPosition, int screenWidth, int screenHeight)
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

void bulletCollisonLimit()
{
    for (int i = 0; i < maxBullets; i++)
    {
        if (bullet[i].isMoving)
        {
            if (bullet[i].position.x < 0)
            {
                bullet[i].isMoving = false;
                bullet[i].isActive = false;
            }

            if (bullet[i].position.x >= screenWidth)
            {
                bullet[i].isMoving = false;
                bullet[i].isActive = false;
            }

            if (bullet[i].position.y < 0)
            {
                bullet[i].isMoving = false;
                bullet[i].isActive = false;
            }

            if (bullet[i].position.y >= screenHeight)
            {
                bullet[i].isMoving = false;
                bullet[i].isActive = false;
            }
        }
    }
}

bool CheckCollsisionCirCir(Vector2 Obj1Pos, float obj1Radius, Vector2 obj2Pos, float obj2Radius)
{
    float distX = Obj1Pos.x - obj2Pos.x;
    float distY = Obj1Pos.y - obj2Pos.y;
    
    float distance = sqrt((distX * distX) + (distY * distY));

    if (distance <= obj1Radius + obj2Radius) 
    {
        return true;
    }

    return false;
}

void AsteroidCollision(Ship& playerShip)
{
    for (int i = 0; i < maxAteroids; i++)
    {
        if (asteroid[i].isActive == true)
        {
            if (CheckCollsisionCirCir(playerShip.position, playerShip.radius, asteroid[i].position, asteroid[i].radius))
            {
                cout << "colision" << endl;
            }
        }
    }
}

void BulletCollision(Asteroid& asteroid)
{
    for (int i = 0; i < maxBullets; i++)
    {
        for (int j = 0; j < maxAteroids; j++)
        {
            if (bullet[i].isActive == true)
            {
                if (asteroid.isActive == true)
                {
                    if (CheckCollsisionCirCir(bullet[i].position, bullet[i].radius, asteroid.position, asteroid.radius))
                    {
                        bullet[i].isMoving = false;
                        asteroid.isActive = false;
                        bullet[i].isActive = false;
                        cout << "colision bala" << endl;
                    }
                }
            }
        }
    }
}

void UnloadData()
{
    UnloadTexture(playerShip.texture);

    for (int i = 0; i < maxAteroids; i++)
    {
        UnloadTexture(asteroid[i].texture);
    }

    for (int i = 0; i < maxBullets; i++)
    {
        UnloadTexture(bullet[i].texture);
    }

    UnloadTexture(mouse.texture);
    UnloadTexture(background);
}