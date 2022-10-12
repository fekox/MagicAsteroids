#include "raylib.h"
#pragma once

struct Ship
{
	Vector2 position;
	Vector2 direction;
	Vector2 aceleration;

	Rectangle dest;
	Rectangle source;

	Rectangle shipRec;
	Vector2 shipOriginRec;
	Vector2 shipDirNormalize;

	float widht;
	float height;

	float rotation;

	float radius;

	float speed;

	int lifes;

	int points;

	bool isCollision;
	bool isAlive;
	bool isActive;
	bool win;

	Texture2D texture;

	Color color;
};

Ship CreateShip();

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight);

void DrawShip(Ship& PlayerShip, Vector2& shipOriginRec, float playerWidth, float playerHeight);

void LoseLife(Ship& playerShip);

void AddPoint(Ship& playerShip);

bool IsAlive(Ship& playerShip);

bool PlayerWin(Ship& playerShip);

int GetPoint();
