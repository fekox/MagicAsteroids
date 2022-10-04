#include "raylib.h"
#pragma once

enum class Size
{
	Big,
	Normal,
	Small
};

struct Asteroid
{
	Vector2 position;

	Size size;

	float radius;

	bool isActive;

	Vector2 speed;

	Texture2D texture;
};

Asteroid CreateAsteroid(Size size);

void DrawAsteroidBig(Asteroid& asteroid);

void DrawAsteroidNormal(Asteroid& asteroid);

void DrawAsteroidSmall(Asteroid& asteroid);
