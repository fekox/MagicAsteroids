#pragma once

struct Ship
{
	float posX;
	float posY;

	float widht;
	float height;

	float speed;

	int lifes;

	int points;
};

Ship CreateShip();

void DrawShip();

void AddPoint();

int GetPoint();
