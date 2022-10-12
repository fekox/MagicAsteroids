#pragma once

#include "raylib.h"


struct Bullet
{
	Vector2 position;

	Vector2 direction;

	bool isMoving;

	bool isActive;

	float radius;

	float speed;

	Texture2D texture;
};

Bullet CreateBullet();

void DrawBullet(Bullet bullet);