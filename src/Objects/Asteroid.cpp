#include "Objects/Asteroid.h"


Asteroid CreateAsteroid(Size size)
{
	Asteroid asteroid;
	Asteroid norAsteroid;
	Asteroid smallAsteroid;

	switch (size)
	{
	case Big:

		asteroid.position.x = GetRandomValue(700, 1000);
		asteroid.position.y = GetRandomValue(700, 900);

		asteroid.radius = 60.0f;

		asteroid.isActive = true;

		asteroid.speed.x = GetRandomValue(-70, 70);
		asteroid.speed.y = GetRandomValue(-70, 70);

		asteroid.texture = LoadTexture("resources/Sprites/Asteroid.png");

		return asteroid;

		break;

	case Normal:

		norAsteroid.position.x = 0;
		norAsteroid.position.y = 0;

		norAsteroid.radius = 45.0f;

		norAsteroid.isActive = false;

		norAsteroid.speed.x = GetRandomValue(-90, 90);
		norAsteroid.speed.y = GetRandomValue(-90, 90);

		norAsteroid.texture = LoadTexture("resources/Sprites/NormalAsteroid.png");

		return norAsteroid;

		break;

	case Small:

		smallAsteroid.position.x = 0;
		smallAsteroid.position.y = 0;

		smallAsteroid.radius = 35.0f;

		smallAsteroid.isActive = false;

		smallAsteroid.speed.x = GetRandomValue(-110, 110);
		smallAsteroid.speed.y = GetRandomValue(-110, 110);

		smallAsteroid.texture = LoadTexture("resources/Sprites/SmallAsteroid.png");

		return smallAsteroid;

		break;
	}
}

void DrawAsteroidBig(Asteroid& asteroid) 
{
	if (asteroid.isActive == true)
	{
		DrawTexture(asteroid.texture, asteroid.position.x - 70, asteroid.position.y - 70, WHITE);
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, BLANK);
	}
}

void DrawAsteroidNormal(Asteroid& asteroid)
{
	if (asteroid.isActive == true)
	{
		DrawTexture(asteroid.texture, asteroid.position.x - 50, asteroid.position.y - 50, WHITE);
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, BLANK);
	}
}

void DrawAsteroidSmall(Asteroid& asteroid)
{
	if (asteroid.isActive == true)
	{
		DrawTexture(asteroid.texture, asteroid.position.x - 40, asteroid.position.y - 40, WHITE);
		DrawCircle(asteroid.position.x, asteroid.position.y, asteroid.radius, BLANK);
	}
}