#include "Objects/Asteroid.h"
#include "Objects/PlayerShip.h"
#pragma once

void Input();
void Update();
void Collision();
void Draw();
void UnloadData();

void shipMovement();
void bulletMovement();

void asteroidMovement();
void AsteroidCollision(Ship& playerShip, Asteroid& asteroid, float radius);
bool CheckCollisionCirRec(Vector2 asteroidPos, float asteroidRadius, Rectangle rect);

void objCollisionLimit(Vector2& shipPosition, int screenWidth, int screenHeight);
void bulletCollisonLimit();

void mouseMovement();

void drawGame();