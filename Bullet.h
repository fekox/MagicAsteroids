#include "raylib.h"
#include "Objects/PlayerShip.h"
#pragma once

struct Bullet
{
	Vector2 position;

	float radius;

	float speed;

	Texture2D texture;
};

Bullet CreateBullet(Ship playerShip);

void DrawBullet(Bullet bullet);

