#include "raylib.h"
#pragma once

struct Bullet
{
	Vector2 position;

	Vector2 direction;

	bool isMoving;

	float radius;

	float speed;

	Texture2D texture;
};

Bullet CreateBullet();

void DrawBullet(Bullet bullet);