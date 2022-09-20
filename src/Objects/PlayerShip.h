#pragma once

struct Ship
{
	float widht;
	float height;

	Vector2 position;

	float speed;

	int lifes;

	int points;
};

Ship CreateShip();

void DrawShip(Ship& PlayerShip);

Vector2 GetShipPosition(Vector2& ShipPosition);

void AddPoint();

int GetPoint();
