#include "Objects/Asteroid.h"


Asteroid CreateAsteroid()
{
	Asteroid asteroid;

	asteroid.position.x = 0;
	asteroid.position.y = 0;

	asteroid.radius = 0;

	asteroid.speed = 0;

	return asteroid;
}

void DrawAsteroid(Asteroid asteroid) 
{
	DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, WHITE);
}