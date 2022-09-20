#include "raylib.h"
#include "Objects/PlayerShip.h"

Ship CreateShip()
{
	Ship playerShip;

	playerShip.position.x = 0;
	playerShip.position.y = 0;

	playerShip.directionX = 0;
	playerShip.directionY = 0;

	playerShip.height = 0;
	playerShip.widht = 0;

	playerShip.angle = 0;

	playerShip.rotation = 0;

	playerShip.speed = 0;

	playerShip.lifes = 0;

	playerShip.points = 0;

	return playerShip;
}

Rectangle CreateRectangleShip(Ship& playerShip)
{
	Rectangle shipRec;

	shipRec.x = playerShip.position.x;
	shipRec.y = playerShip.position.y;

	shipRec.width = playerShip.widht;
	shipRec.height = playerShip.height;

	return shipRec;
}

Vector2 CreateRecOriginShip(Rectangle& shipRec)
{
	Vector2 shipOriginRec;

	shipOriginRec.x = shipRec.width / 2;
	shipOriginRec.y = shipRec.width / -2;

	return shipOriginRec;
}

void shipTeleport(Vector2& shipPosition, int screenWidth, int screenHeight)
{
	if (shipPosition.x < 0)
	{
		shipPosition.x = screenWidth;
	}

	if (shipPosition.x >= screenWidth)
	{
		shipPosition.x = screenWidth;
	}

	if (shipPosition.y < 0)
	{
		shipPosition.y = screenHeight;
	}

	if (shipPosition.y >= screenHeight)
	{
		shipPosition.y = screenHeight;
	}
}

void DrawShip(Ship& playerShip, Rectangle& shipRec)
{
	DrawRectanglePro(CreateRectangleShip(playerShip), CreateRecOriginShip(shipRec), playerShip.rotation, RED);
}

void AddPoint()
{

}

int GetPoint()
{


	return 1;
}