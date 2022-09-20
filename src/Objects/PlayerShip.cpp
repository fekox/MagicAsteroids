#include "raylib.h"
#include "Objects/PlayerShip.h"

Ship CreateShip()
{
	Ship playerShip;

	playerShip.position.x = 0;
	playerShip.position.y = 0;

	playerShip.direction.x = 0;
	playerShip.direction.y = 0;

	playerShip.height = 0;
	playerShip.widht = 0;

	playerShip.angle = 0;

	playerShip.rotation = 0;

	playerShip.speed = 0;

	playerShip.lifes = 0;

	playerShip.points = 0;

	return playerShip;
}

void DrawShip(Ship &PlayerShip)
{
	DrawRectangle(PlayerShip.position.x, PlayerShip.position.y, PlayerShip.widht, PlayerShip.height, RED);
}

Vector2 GetShipPosition(Vector2& ShipPosition)
{
	return ShipPosition;
}

void AddPoint()
{

}

int GetPoint()
{


	return 1;
}