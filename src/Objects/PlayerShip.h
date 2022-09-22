#pragma once

struct Ship
{
	Vector2 position;
	Vector2 direction;
	Vector2 aceleration;

	Rectangle dest;
	Rectangle source;

	float widht;
	float height;

	float rotation;

	float speed;

	int lifes;

	int points;

	Texture2D texture;
};

Ship CreateShip();

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight);

void DrawShip(Ship& PlayerShip, Vector2& shipOriginRec);

void AddPoint();

int GetPoint();
