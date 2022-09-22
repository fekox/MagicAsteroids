#include "raylib.h"
#pragma once

struct Asteroid
{
	Vector2 position;

	//Rectangle dest;
	//Rectangle source;

	float radius;

	Color color;

	float speed;

	Texture2D texture;
};

Asteroid CreateAsteroid();

void DrawAsteroid(Asteroid asteroid);
