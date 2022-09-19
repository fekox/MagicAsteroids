#pragma once

struct Ship
{
	float posX;
	float posY;

	float widht;
	float height;

	Vector2 rotation;

	float speed;

	int lifes;

	int points;
};

Ship CreateShip();

void DrawShip(Ship& PlayerShip);

void AddPoint();

int GetPoint();
