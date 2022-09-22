#include "Objects/Asteroid.h"


Asteroid CreateAsteroid()
{
	Asteroid asteroid;

	asteroid.position.x = 100.0f;
	asteroid.position.y = 100.0f;

	asteroid.speed = 50.0f;

	asteroid.radius = 80.0f;

	return asteroid;
}

void DrawAsteroid(Asteroid asteroid) 
{
	DrawCircleV(asteroid.position, asteroid.radius, WHITE);
}