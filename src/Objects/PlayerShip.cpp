#include <iostream>
#include "raylib.h"
#include "Objects/PlayerShip.h"

using namespace std;

Ship CreateShip()
{
	Ship playerShip;

	playerShip.position.x = GetScreenWidth() / 2;
	playerShip.position.y = GetScreenHeight() / 2;

	playerShip.direction.x = 0;
	playerShip.direction.y = 0;

	playerShip.aceleration.x = 100.0f;
	playerShip.aceleration.y = 100.0f;

	playerShip.height = 60.0f;
	playerShip.widht = 60.0f;

	playerShip.rotation = 0;

	playerShip.speed = 100.0f;

	playerShip.lifes = 3;

	playerShip.points = 0;

	playerShip.texture;

	return playerShip;
}

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight)
{
	return Rectangle{ playerShip.position.x - playerWidth / 2, playerShip.position.y - playerHeight / 2, playerWidth, playerHeight };
}

Vector2 CreateRecOriginShip(Rectangle& shipRec)
{
	Vector2 shipOriginRec;

	shipOriginRec.x = shipRec.width / 2;
	shipOriginRec.y = shipRec.height / 2;

	return shipOriginRec;
}

void DrawShip(Ship& playerShip, Rectangle& shipRec)
{
	DrawRectanglePro(GetRec(playerShip, playerShip.widht, playerShip.height), CreateRecOriginShip(shipRec), playerShip.rotation, RED);
}

void AddPoint()
{

}

int GetPoint()
{


	return 1;
}