#include "raylib.h"
#pragma once

struct Asteroid
{
	Vector2 position;

	float radius;

	Vector2 speed;

	Texture2D texture;
};

Asteroid CreateAsteroid();

void DrawAsteroid(Asteroid asteroid);
