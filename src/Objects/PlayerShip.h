#pragma once

struct Ship
{
	Vector2 position;
	
	Vector2 direction;

	Vector2 aceleration;

	float widht;
	float height;

	float angle;

	float rotation;

	float speed;

	int lifes;

	int points;

	Texture2D texture;

	float frameWidth;
	float frameHeight;
};

Ship CreateShip();

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight);

Vector2 CreateRecOriginShip(Rectangle& shipRec);

void DrawShip(Ship& PlayerShip, Rectangle& shipRec);

void AddPoint();

int GetPoint();
