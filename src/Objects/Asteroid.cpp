#include "Objects/Asteroid.h"


Asteroid CreateAsteroid()
{
	Asteroid asteroid;

	asteroid.position.x = GetRandomValue(0, 1024);
	asteroid.position.y = GetRandomValue(0, 768);

	asteroid.speed.x = GetRandomValue(-70, 70);
	asteroid.speed.y = GetRandomValue(-70, 70);

	asteroid.radius = 60.0f;

	asteroid.texture = LoadTexture("resources/Asteroid.png");

	return asteroid;
}

void DrawAsteroid(Asteroid asteroid) 
{
	DrawTexture(asteroid.texture, asteroid.position.x - 70, asteroid.position.y - 70, WHITE);
	DrawCircleV(asteroid.position, asteroid.radius, BLANK);
}