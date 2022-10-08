#include "raylib.h"
#include "Objects/PlayerShip.h"

using namespace std;

Ship CreateShip()
{
	Ship playerShip;

	playerShip.position.x = static_cast<float>(GetScreenWidth() / 2);
	playerShip.position.y = static_cast<float>(GetScreenHeight() / 2);

	playerShip.direction.x = 0;
	playerShip.direction.y = 0;

	playerShip.aceleration.x = 50.0f;
	playerShip.aceleration.y = 50.0f;

	playerShip.height = 60.0f;
	playerShip.widht = 60.0f;

	playerShip.radius = 25.0f;

	playerShip.rotation = 0;

	playerShip.speed = 100.0f;

	playerShip.lifes = 3;

	playerShip.points = 0;

	playerShip.isCollision = false;

	playerShip.isAlive = true;

	playerShip.isActive = true;

	playerShip.texture = LoadTexture("resources/Sprites/Ship.png");

	playerShip.color.a = 255;
	playerShip.color.b = 255;
	playerShip.color.g = 255;
	playerShip.color.r = 255;

	return playerShip;
}

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight)
{
	return Rectangle{ playerShip.position.x - playerWidth / 2, playerShip.position.y - playerHeight / 2, playerWidth, playerHeight };
}

void DrawShip(Ship& playerShip, Vector2& shipOriginRec, float playerWidth, float playerHeight)
{
	if (playerShip.isActive)
	{
		DrawTexturePro(playerShip.texture, Rectangle{ 0,0, static_cast<float>(playerShip.texture.width), static_cast<float>(playerShip.texture.height) }, Rectangle{ playerShip.position.x - playerShip.widht / 2, playerShip.position.y - playerShip.height / 2, playerShip.widht, playerShip.height }, shipOriginRec, playerShip.rotation, playerShip.color);
		DrawCircle(static_cast<int>(playerShip.position.x - playerWidth / 2), static_cast<int>(playerShip.position.y - playerHeight / 2), playerShip.radius, BLANK);
	}
}

void loseLife(Ship& playerShip)
{
	if (playerShip.isCollision == true)
	{
		playerShip.lifes -= 1;
	}
}

bool IsAlive(Ship& playerShip)
{
	if (playerShip.lifes <= 0)
	{
		return playerShip.isAlive == false;
	}

	else
	{
		return playerShip.isAlive == true;
	}
}

void AddPoint(Ship& playerShip)
{
	playerShip.points += 10;
}

int GetPoint()
{
	return 1;
}