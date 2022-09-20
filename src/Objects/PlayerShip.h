#pragma once

struct Ship
{
	Vector2 position;
	Vector2 direction;

	float widht;
	float height;

	float angle;

	float rotation;

	float speed;

	int lifes;

	int points;
};

Ship CreateShip();

void DrawShip(Ship& PlayerShip);

Vector2 GetShipPosition(Vector2& ShipPosition);

Vector2 GetShipDirection(Vector2& ShipDirection);

void AddPoint();

int GetPoint();
