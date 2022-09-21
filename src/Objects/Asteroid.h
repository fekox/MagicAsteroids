#include "raylib.h"
#pragma once

struct Asteroid
{
	Vector2 position;

	Vector2 colisionPos;

	float radius;

	Color color;

	float speed;
};

Asteroid CreateAsteroid();

void DrawAsteroid(Asteroid asteroid);
