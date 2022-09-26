#include "raylib.h"
#pragma once

struct Asteroid
{
	Vector2 position;

	float radius;

	bool isActive;

	Vector2 speed;

	Texture2D texture;
};

Asteroid CreateAsteroid();

void DrawAsteroid(Asteroid asteroid);
