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

	Texture2D texture;
};

Ship CreateShip();

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight);

void DrawShip(Ship& PlayerShip, Vector2& shipOriginRec, float playerWidth, float playerHeight);

void AddPoint(Ship& playerShip);

int GetPoint();
