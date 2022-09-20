#pragma once

struct Ship
{
	Vector2 position;
	
	float directionX;
	float directionY;

	float widht;
	float height;

	float angle;

	float rotation;

	float speed;

	int lifes;

	int points;
};

Ship CreateShip();

Rectangle CreateRectangleShip(Ship& PlayerShip);

Vector2 CreateRecOriginShip(Rectangle& shipRec);

void shipTeleport(Vector2& shipPosition, int screenWidth, int screenHeight);

void DrawShip(Ship& PlayerShip, Rectangle& shipRec);

void AddPoint();

int GetPoint();
