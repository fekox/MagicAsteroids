#pragma once

struct Asteroid
{
	float posX;
	float posY;

	float widht;
	float height;

	float speed;

};

Asteroid CreateAsteroid();

void DrawAsteroid();
