#include "Objects/Asteroid.h"


Asteroid CreateAsteroid()
{
	Asteroid asteroid;

	asteroid.position.x = GetRandomValue(0, 1024);
	asteroid.position.y = GetRandomValue(0, 768);

	asteroid.radius = 60.0f;

	asteroid.isActive = true;

	asteroid.speed.x = GetRandomValue(-70, 70);
	asteroid.speed.y = GetRandomValue(-70, 70);

	asteroid.texture = LoadTexture("resources/Asteroid.png");

	return asteroid;
}

void DrawAsteroid(Asteroid asteroid) 
{
	if (asteroid.isActive == true)
	{
		DrawTexture(asteroid.texture, asteroid.position.x - 70, asteroid.position.y - 70, WHITE);
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, BLANK);
	}
}