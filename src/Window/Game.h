#include "Objects/Asteroid.h"
#include "Objects/PlayerShip.h"
#pragma once

void shipMovement();
void shipTeleport(Vector2& shipPosition, int screenWidth, int screenHeight);

void AsteroidCollision(Ship& playerShip, Asteroid& asteroid, float radius);
bool CheckCollisionCirRec(Vector2 asteroidPos, float asteroidRadius, Rectangle rect);

void mouseMovement();

void drawGame();