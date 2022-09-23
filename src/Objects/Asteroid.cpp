#include "Objects/Asteroid.h"


Asteroid CreateAsteroid()
{
	Asteroid asteroid;

	asteroid.position.x = 100.0f;
	asteroid.position.y = 100.0f;

	asteroid.speed = 50.0f;

	asteroid.radius = 60.0f;

	asteroid.texture = LoadTexture("resources/Asteroid.png");

	return asteroid;
}

void DrawAsteroid(Asteroid asteroid) 
{
	DrawCircleV(asteroid.position, asteroid.radius, BLANK);
	DrawTexture(asteroid.texture, asteroid.position.x - 70, asteroid.position.y - 70, WHITE);
}