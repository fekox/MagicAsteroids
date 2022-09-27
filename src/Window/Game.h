#include "Objects/Asteroid.h"
#include "Objects/PlayerShip.h"
#include "Objects/Bullet.h"
#pragma once

void Input();
void Update();
void Collision();
void Draw();
void UnloadData();

void shipMovement();
void bulletMovement();

void asteroidMovement();
void AsteroidCollision(Ship& playerShip);
void BulletCollision();
bool CheckCollsisionCirCir(Vector2 Obj1Pos, float obj1Radius, Vector2 obj2Pos, float obj2Radius);

void objCollisionLimit(Vector2& shipPosition, int screenWidth, int screenHeight);
void bulletCollisonLimit();

void mouseMovement();

void drawGame();