#include "Objects/Asteroid.h"


Asteroid CreateAsteroid(Size size)
{
	Asteroid asteroid;
	Asteroid norAsteroid;
	Asteroid smallAsteroid;

	switch (size)
	{
	case Big:

		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);

		asteroid.radius = 60.0f;

		asteroid.isActive = true;

		asteroid.speed.x = GetRandomValue(-70, 70);
		asteroid.speed.y = GetRandomValue(-70, 70);

		asteroid.texture = LoadTexture("resources/Asteroid.png");

		return asteroid;

		break;

	case Normal:

		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);

		norAsteroid.position.x = asteroid.position.x;
		norAsteroid.position.y = asteroid.position.y;

		norAsteroid.radius = 45.0f;

		norAsteroid.isActive = true;

		norAsteroid.speed.x = GetRandomValue(-90, 90);
		norAsteroid.speed.y = GetRandomValue(-90, 90);

		norAsteroid.texture = LoadTexture("resources/NormalAsteroid.png");

		return norAsteroid;

		break;

	case Small:

		asteroid.position.x = GetRandomValue(0, 1024);
		asteroid.position.y = GetRandomValue(0, 768);

		norAsteroid.position.x = asteroid.position.x;
		norAsteroid.position.y = asteroid.position.y;

		smallAsteroid.position.x = asteroid.position.x;
		smallAsteroid.position.y = asteroid.position.y;

		smallAsteroid.radius = 35.0f;

		smallAsteroid.isActive = true;

		smallAsteroid.speed.x = GetRandomValue(-110, 110);
		smallAsteroid.speed.y = GetRandomValue(-110, 110);

		smallAsteroid.texture = LoadTexture("resources/SmallAsteroid.png");

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