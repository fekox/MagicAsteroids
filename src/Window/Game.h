#include "Objects/Asteroid.h"
#include "Objects/PlayerShip.h"
#pragma once

void shipMovement();

void asteroidMovement();
void AsteroidCollision(Ship& playerShip, Asteroid& asteroid, float radius);
bool CheckCollisionCirRec(Vector2 asteroidPos, float asteroidRadius, Rectangle rect);

void objTeleport(Vector2& shipPosition, int screenWidth, int screenHeight);

void mouseMovement();

void drawGame();