#include "Objects/Asteroid.h"

Asteroid CreateAsteroid(Size size, Asteroid& asteroid)
{
	switch (size)
	{
		case Size::Big:

		asteroid.size = Size::Big;
		asteroid.position.x = static_cast<float>(GetRandomValue(700, 1000));
		asteroid.position.y = static_cast<float>(GetRandomValue(700, 900));

		asteroid.radius = 60.0f;

		asteroid.isActive = true;

		asteroid.speed.x = static_cast<float>(GetRandomValue(-70, 70));
		asteroid.speed.y = static_cast<float>(GetRandomValue(-70, 70));

		asteroid.texture = LoadTexture("resources/Sprites/Asteroid.png");
		
		break;

		case Size::Normal:

		asteroid.size = Size::Normal;
		asteroid.position.x = 0;
		asteroid.position.y = 0;

		asteroid.radius = 45.0f;

		asteroid.isActive = false;

		asteroid.speed.x = static_cast<float>(GetRandomValue(-90, 90));
		asteroid.speed.y = static_cast<float>(GetRandomValue(-90, 90));

		asteroid.texture = LoadTexture("resources/Sprites/NormalAsteroid.png");
		
		break;

		case Size::Small:

		asteroid.size = Size::Small;
		asteroid.position.x = 0;
		asteroid.position.y = 0;

		asteroid.radius = 35.0f;

		asteroid.isActive = false;

		asteroid.speed.x = static_cast<float>(GetRandomValue(-110, 110));
		asteroid.speed.y = static_cast<float>(GetRandomValue(-110, 110));

		asteroid.texture = LoadTexture("resources/Sprites/SmallAsteroid.png");
		
		break;
	}

	return asteroid;
}

void DrawAsteroidBig(Asteroid& asteroid) 
{
	if (asteroid.isActive == true)
	{
		DrawTexture(asteroid.texture, static_cast<int>(asteroid.position.x - 70), static_cast<int>(asteroid.position.y -70), WHITE);
		DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.radius, BLANK);
	}
}

void DrawAsteroidNormal(Asteroid& asteroid)
{
	if (asteroid.isActive == true)
	{
		DrawTexture(asteroid.texture, static_cast<int>(asteroid.position.x - 50), static_cast<int>(asteroid.position.y - 50), WHITE);
		DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.radius, BLANK);
	}
}

void DrawAsteroidSmall(Asteroid& asteroid)
{
	if (asteroid.isActive == true)
	{
		DrawTexture(asteroid.texture, static_cast<int>(asteroid.position.x - 40), static_cast<int>(asteroid.position.y - 40), WHITE);
		DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.radius, BLANK);
	}
}