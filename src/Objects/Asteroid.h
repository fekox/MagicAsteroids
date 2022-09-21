#include "raylib.h"
#pragma once

struct Asteroid
{
	Vector2 position;

	float radius;

	Color color;

	float speed;
};

Asteroid CreateAsteroid();

void DrawAsteroid(Asteroid asteroid);
