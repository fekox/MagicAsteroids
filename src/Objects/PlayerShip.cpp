#include <iostream>
#include "raylib.h"
#include "Objects/PlayerShip.h"

using namespace std;

Ship CreateShip()
{
	Ship playerShip;

	playerShip.position.x = 0;
	playerShip.position.y = 0;

	playerShip.direction.x = 0;
	playerShip.direction.y = 0;

	playerShip.aceleration.x = 0;
	playerShip.aceleration.y = 0;

	playerShip.height = 0;
	playerShip.widht = 0;

	playerShip.angle = 0;

	playerShip.rotation = 0;

	playerShip.speed = 0;

	playerShip.lifes = 0;

	playerShip.points = 0;

	return playerShip;
}

Rectangle GetRec(Ship& playerShip, float playerWidth, float playerHeight)
{
	return Rectangle{ playerShip.position.x - playerWidth / 2, playerShip.position.y - playerHeight / 2, playerWidth, playerHeight };
}

Vector2 CreateRecOriginShip(Rectangle& shipRec)
{
	Vector2 shipOriginRec;

	shipOriginRec.x = shipRec. height / 2;
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